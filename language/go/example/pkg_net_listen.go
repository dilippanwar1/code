// The Listen function creates server.
package main

import (
	"fmt"
	"net"
	"os"
)

func handleConnection(c net.Conn) {
	// E.g. Get request from [::1]:49985 to [::1]:8080.
	fmt.Printf("Get request from %s to %s.\n", c.RemoteAddr(), c.LocalAddr())
}

func main() {

	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("Error listening on tcp:8080")
		os.Exit(1)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		go handleConnection(conn)
	}
}
