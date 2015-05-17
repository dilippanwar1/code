// About DNS in general:
//   https://www.digitalocean.com/community/tutorials/an-introduction-to-dns-terminology-components-and-concepts
// Search domain:
//   http://superuser.com/questions/184361/what-is-the-search-domains-field-for-in-the-tcp-ip-dns-settings-control-panel
//
// Record Types:
//   A: Name -> IP address
//   NS: Name -> Authoritative nameserver ("referrals")
//   MX: Name -> Mail server
//   CNAME: Canonical name
//   PTR: IP address -> Name
//   AAAA: Name -> IPv6 address
// Example1:
//   $ dig www.gatech.edu
//   ;; OPT PSEUDOSECTION:
//   ; EDNS: version: 0, flags:; udp: 4000
//   ;; QUESTION SECTION:
//   ;www.gatech.edu.                        IN      A
//   ;; ANSWER SECTION:
//   www.gatech.edu.         60      IN      CNAME   tlweb.gtm.gatech.edu.
//   tlweb.gtm.gatech.edu.   30      IN      A       130.207.244.165
// The ANSWER SECTION tells that what you asked for is www.gatech.edu., but what
// you really want to ask is tlweb.gtm.gatech.edu (which is a CNAME record). The
// second line returns the IP address for tlweb.gtm.gatech.edu. The number 60, 30
// means TTL for the record.
//
// Example2:
//   $ dig nytimes.com
//   ;; OPT PSEUDOSECTION:
//   ; EDNS: version: 0, flags:; udp: 4000
//   ;; QUESTION SECTION:
//   ;nytimes.com.                   IN      A
//
//   ;; ANSWER SECTION:
//   nytimes.com.            71      IN      A       170.149.172.130
//   nytimes.com.            71      IN      A       170.149.168.130
// The ANSWER SECTION has two records, both belong to nytimes.com., mostly for
// load balance.
//
// Example3:
//   $ dig ns gatech.edu
//   $ dig mx gatech.edu
//   $ dig +trace gatech.edu
//   $ dig +trace -x 130.207.7.36
//
//
// Steps for running skydns example (Ubuntu14.04):
// 1. $ etcd
// 2. $ sudo ./skydns -addr=127.0.2.2:53 -nameservers=8.8.8.8:53
//   For now, we have an etcd instance running, and a skydns server runing at 127.0.2.2:53,
//   the skydns instance will use etcd as backend (127.0.0.1:4001 by default). If it can't
//   find dns entry, skydns will forward request to name resolving server 8.8.8.8:53. Note
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
