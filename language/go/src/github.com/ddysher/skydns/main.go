// About DNS in general:
//   https://www.digitalocean.com/community/tutorials/an-introduction-to-dns-terminology-components-and-concepts
//
// Steps (Ubuntu14.04):
// 1. $ etcd
// 2. $ sudo ./skydns -addr=127.0.2.2:53 -nameservers=8.8.8.8:53
//   For now, we have an etcd instance running, and a skydns server runing at 127.0.2.2:53,
//   the skydns instance will use etcd as backend (127.0.0.1:4001 by default). If it cann't
//   find dns entry, skydns will forward request to name resolving server 8.8.8.8:53.  Note
//   skyDNS is running at the default dns port udp:53, so we need to run it as root. An
//   alternative solution might be using iptables.
// 3. Edit /etc/resolv.conf, add "nameserver 127.0.2.2" to TOP of file.
//   The reason we use standard port 53 for skydns is due to this file - it assumes port 53
//   for the given ip address. Also, we need to add 127.0.2.2 as the first nameserver due to
//   resolusion order, or just remove all other entries. At this point, we can use `dip` or
//   `host` command to query skydns, but we can NOT use `ping`, because of dns multicast.
// 4. Edit /etc/nsswitch.conf, change
//     hosts:          files mdns4_minimal [NOTFOUND=return] dns
//   To:
//     hosts:          files dns
//   See http://askubuntu.com/questions/81797/nslookup-finds-ip-but-ping-doesnt
//   Now we are ready to go!
// 5. $ go run main.go
// 6. Revert changes to /etc/resolv.conf and /etc/nsswitch.conf.
//
// Alternative iptable solution:
// If running as root is not desirable, we can use the following steps. Note that since we
// change the iptable for udp port 53, we don't have to change /etc/resolv.conf anymore.
// 1. $ etcd
// 2. $ skydns -addr=127.0.0.1:1053 -nameservers=8.8.8.8:53
// 3. $ sudo iptables -t nat -A OUTPUT -p udp --dport 53 -j DNAT --to-destination 127.0.0.1:1053
//   Great artical about iptables:
//     https://www.digitalocean.com/community/tutorials/how-to-set-up-a-firewall-using-iptables-on-ubuntu-14-04
//     https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/3/html/Reference_Guide/s1-iptables-options.html
//   Options:
//     -t nat: Use NAT table.
//     -A OUTPUT: Append the rule to OUTPUT chain.
//     -p upd: This option matches packets if the protocol being used is UPD.
//     --dport 53: This option is available if the -p tcp flag is given. It gives a
//       further requirement of matching the destination port for the matching packet.
//     -j DNAT: DNAT is an extended target module (standard ones are ACCEPT, DROP, QUEUE,
//       and RETURN. DNAT is only valid in the nat table, in the PREROUTING and OUTPUT
//       chains, and user-defined chains which are only called from those chains. It
//       specifies that the destination address of the packet should be modified (and all
//       future packets in this connection will also be mangled), and rules should cease
//       being examined.
//     --to-destination 127.0.0.1:1053: This option is available for '-j DNAT' option. It
//       is used to specify a single new destication IP address and port.
// 4. Edit /etc/nsswitch.conf, change
//     hosts:          files mdns4_minimal [NOTFOUND=return] dns
//   To:
//     hosts:          files dns
// 5. $ go run main.go
// 6. Revert changes to /etc/nsswitch.conf and delete iptables rule.
//     $ sudo iptables -t nat -D OUTPUT -p udp --dport 53 -j DNAT --to-destination 127.0.0.1:1053

package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"net"
	"net/http"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/coreos/go-etcd/etcd"
)

type AddrRecord struct {
	Host string
	Port int
}

func main() {
	client, err := newEtcdClient()
	if err != nil {
		fmt.Println("error connect to etcd:", err)
		os.Exit(1)
	}

	// Create three services.
	go RunService("srv01.east.skydns.local", "127.0.0.1:8888", client)
	go RunService("srv02.west.skydns.local", "127.0.0.1:8889", client)
	go RunService("srv03.west.skydns.local", "127.0.0.1:8890", client)

	// A silly sleep to wait for all services up...
	fmt.Println("Wait for all services to up...")
	time.Sleep(time.Second)

	// Try resolving one hostname.
	ips, err := net.LookupHost("srv01.east.skydns.local")
	if err != nil {
		fmt.Println("error lookup host:", err)
		os.Exit(1)
	}
	fmt.Println("IPs for srv03.west.skydns.local:", ips)

	// Try talking to one service.
	clientHTTP := &http.Client{}
	res, err := clientHTTP.Get("http://srv03.west.skydns.local:8890/hello")
	if err != nil {
		fmt.Println("error connecting to srv03.west.skydns.local:", err)
		os.Exit(1)
	}
	fmt.Println("Returned from server:", res.Status)
	scanner := bufio.NewScanner(res.Body)
	for scanner.Scan() {
		fmt.Println("Message From server:", scanner.Text())
	}
	res.Body.Close()
}

// RunService creates and runs a service. 'domain' must be a '.' separated and 'address'
// must be 'host:port' pair.
func RunService(domain, addr string, client *etcd.Client) {
	_, err := client.Set(domainToEtcdKey(domain), getAddressRecord(addr), 0)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	mux := http.NewServeMux()
	mux.HandleFunc("/hello", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "Hello world from service %s Go program!\n", domain)
	})
	http.ListenAndServe(addr, mux)
}

// newEtcdClient returns new client if we can connect to etcd; otherwise, return nil and err.
func newEtcdClient() (*etcd.Client, error) {
	client := etcd.NewClient([]string{})
	if _, err := client.Get("/", false, false); err != nil {
		return nil, err
	}
	return client, nil
}

// getAddressRecord retruns a json representation of AddrRecord. Note the record in etcd is:
//  {..., "key":"/skydns/local/skydns/west/srv03","value":"{\"Host\":\"127.0.0.1\",\"Port\":8890}", ... }
// Not
//  {..., "key":"/skydns/local/skydns/west/srv03","value":"{Host:127.0.0.1,Port:8890}", ... }
// i.e. we can't simply do:
//  client.Set(domainToEtcdKey(domain), fmt.Sprintf("{Host:127.0.0.1,Port:8890}"), 0)
func getAddressRecord(addr string) string {
	host, port, _ := net.SplitHostPort(addr)
	portInt, _ := strconv.Atoi(port)
	addrRecord := AddrRecord{Host: host, Port: portInt}
	b, err := json.Marshal(addrRecord)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	return string(b)
}

// domainToEtcdKey converts domain to skydns etcd key, e.g. "srv03.west.skydns.local" to "skydns/local/skydns/west/srv03"
func domainToEtcdKey(domain string) string {
	parts := strings.Split(domain, ".")
	for i, j := 0, len(parts)-1; i < j; i, j = i+1, j-1 {
		parts[i], parts[j] = parts[j], parts[i]
	}
	return "skydns/" + strings.Join(parts, "/")
}
