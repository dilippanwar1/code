package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
)

func main() {
	// Dial is a low-level function used to connect to a server. Document from
	// Go package:
	//
	// Dial connects to the address on the named network.
	//
	// Known networks are "tcp", "tcp4" (IPv4-only), "tcp6" (IPv6-only),
	// "udp", "udp4" (IPv4-only), "udp6" (IPv6-only), "ip", "ip4"
	// (IPv4-only), "ip6" (IPv6-only), "unix", "unixgram" and
	// "unixpacket".
	//
	// For TCP and UDP networks, addresses have the form host:port.
	// If host is a literal IPv6 address it must be enclosed
	// in square brackets as in "[::1]:80" or "[ipv6-host%zone]:80".
	// The functions JoinHostPort and SplitHostPort manipulate addresses
	// in this form.
	//
	// Examples:
	//	Dial("tcp", "12.34.56.78:80")
	//	Dial("tcp", "google.com:http")
	//	Dial("tcp", "[2001:db8::1]:http")
	//	Dial("tcp", "[fe80::1%lo0]:80")
	//
	// For IP networks, the network must be "ip", "ip4" or "ip6" followed
	// by a colon and a protocol number or name and the addr must be a
	// literal IP address.
	//
	// Examples:
	//	Dial("ip4:1", "127.0.0.1")
	//	Dial("ip6:ospf", "::1")
	//
	// For Unix networks, the address must be a file system path.
	conn, err := net.Dial("tcp", "google.com:80")
	if err != nil {
		fmt.Println("Error dailing to google.com:80")
		os.Exit(1)
	}
	fmt.Fprintf(conn, "GET / HTTP/1.0\r\n\r\n")
	status, err := bufio.NewReader(conn).ReadString('\n')
	fmt.Printf(status)

	// E.g. From 74.125.226.4:80 to 10.0.0.5:49950
	fmt.Printf("From %s to %s\n", conn.RemoteAddr(), conn.LocalAddr())
}
