package main

import (
	"fmt"
	"net"
	"os"
	"reflect"
)

var (
	// Aliased, useful to do mocking, etc.
	lookupIP = net.LookupIP
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s ip-addr\n", os.Args[0])
		os.Exit(1)
	}
	name := os.Args[1]

	addr := net.ParseIP(name)
	fmt.Println(reflect.TypeOf(name)) // string
	fmt.Println(reflect.TypeOf(addr)) // net.IP
	// Print the dotted IPv4 or colon IPv6 address (net.IP implemented the
	// Stringer interface, which has a method String() used to print value).
	fmt.Println(addr)
	if addr == nil {
		fmt.Println("Invalid address")
	} else {
		fmt.Println("The address is", addr.String())
	}

	addrs, _ := lookupIP("google.com")
	fmt.Println(addrs)

	os.Exit(0)
}
