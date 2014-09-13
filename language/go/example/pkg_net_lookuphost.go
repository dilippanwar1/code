// The function ResolveIPAddr will perform a DNS lookup on a hostname,
// and return a single IP address. However, hosts may have multiple IP
// addresses, usually from multiple network interface cards. They may
// also have multiple host names, acting as aliases. LookupHost will
// return all IP addresses.
package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s hostname\n", os.Args[0])
		os.Exit(1)
	}
	name := os.Args[1]

	addrs, err := net.LookupHost(name)
	if err != nil {
		fmt.Println("Error: ", err.Error())
		os.Exit(2)
	}

	for _, s := range addrs {
		fmt.Println(s)
	}
	os.Exit(0)
}
