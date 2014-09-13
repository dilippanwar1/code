package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	if len(os.Args) != 3 {
		fmt.Fprintf(os.Stderr,
			"Usage: %s network-type addreee\n",
			os.Args[0])
		os.Exit(1)
	}
	networkType := os.Args[1]
	address := os.Args[2]

	// The type TCPAddr is a structure containing an IP and a port. The
	// function to create a TCPAddr is ResolveTCPAddr, where net is one
	// of "tcp", "tcp4" or "tcp6" and the addr is a string composed of
	// a host name or IP address, followed by port number, for example,
	// "127.0.0.1:80".
	tcpAddr, err := net.ResolveTCPAddr(networkType, address)
	if err != nil {
		fmt.Println("Error: ", err.Error())
		os.Exit(2)
	}

	fmt.Println("Resolved TCP Address ", tcpAddr)
	os.Exit(0)

	// Same thing to UDP Address.
	udpAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8000")
	fmt.Println("Resolved UDP Address ", udpAddr)
}
