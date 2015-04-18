// Experiment with network address resolution.
package main

import (
	"fmt"
	"net"
)

func main() {
	// ResolveTCPAddr(net, addr) parses addr as a TCP address of the form "host:port"
	// or "[ipv6-host%zone]:port". The return type 'TCPAddr' is a structure containing
	// an IP and a port. net param is "tcp", "tcp4" or "tcp6", and the addr param is a
	// string composed of a host name or IP address, followed by port number, e.g.
	// "127.0.0.1:8080", "google.com:80", etc.
	tcpAddr, err := net.ResolveTCPAddr("tcp", "google.com:80")
	if err != nil {
		fmt.Println("Error calling ResolveTCPAddr:", err)
	}
	fmt.Println("Resolved TCP Address:", tcpAddr)

	// There is also a ResolveUDPAddr function.
	udpAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8000")
	if err != nil {
		fmt.Println("Error calling ResolveUDPAddr:", err)
	}
	fmt.Println("Resolved UDP Address:", udpAddr)

	// There is also a ResolveIPAddr function.
	ipAddr, err := net.ResolveIPAddr("ip", "google.com")
	if err != nil {
		fmt.Println("Error calling ResolveIPAddr:", err)
	}
	fmt.Println("Resolved IP address: ", ipAddr.String())

	// The function ResolveIPAddr above will perform a DNS lookup on a hostname, and
	// return a single IP address. However, hosts may have multiple IP addresses,
	// usually from multiple network interface cards. They may also have multiple host
	// names, acting as aliases. LookupHost will return all IP addresses. Note that
	// ResolveIPAddr and LookupHost do not take port, only hostname.
	addrs, err := net.LookupHost("google.com")
	if err != nil {
		fmt.Println("Error calling LookupHost:", err)
	}
	for _, s := range addrs {
		fmt.Printf("%s ", s)
	}
	fmt.Println()

	// LookupIP will also return all IP addresses, in the form of 'addrs []IP'.
	// LookupHost returns 'addrs []string'. Internally, LookupHost calls LookupIP
	// and convert typ IP to string.
	ips, _ := net.LookupIP("google.com")
	if err != nil {
		fmt.Println("Error calling LookupHost:", err)
	}
	fmt.Println(ips)

	// There are many "standard" ports. On a Unix system, the commonly used ports are
	// listed in the file /etc/services. Go has a function to interrogate this file:
	// LookupPort(network, service string). The network argument is a string such as
	// "tcp" or "udp", while the service is a string such as "telnet" or "domain" (for DNS).
	// For example, telnet runs on tcp/23, passing ("tcp", "telnet") will get port 23;
	// however, passing ("udp", "telnet") will get error.
	port, err := net.LookupPort("tcp", "telnet")
	if err != nil {
		fmt.Println("Error calling LookupPort:", err)
	}
	fmt.Println("Service port", port)

	// LookupAddr will do a reverse lookup, i.e. ip address => hostname. For example:
	// file '/etc/hosts' defines lookup entries which maps from hostname to ip address
	// If the file content is:
	//   127.0.0.1  localhost
	//   127.0.1.1  dhcp-100-100-2-84.corp.google.com	dhcp-100-100-2-84
	//   ::1        localhost localhost.localdomain localhost6 localhost6.localdomain6
	// Then we get:
	//   [localhost localhost.localdomain localhost6 localhost6.localdomain6]
	// The '/etc/hosts' file applies to other local resolution as well.
	hosts, err := net.LookupAddr("::1")
	if err != nil {
		fmt.Println("Error calling LookupAddr:", err)
	}
	fmt.Println("Address hosts", hosts)
}
