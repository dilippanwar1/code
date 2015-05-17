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
	client := etcd.NewClient([]string{})

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
