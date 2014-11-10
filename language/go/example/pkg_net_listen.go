// The Listen function creates server.
package main

import (
	"fmt"
	"net"
	"os"
)

func handleConnection(c net.Conn) {
	// E.g. Get request from [::1]:49985 to [::1]:8080. Here, the remote address
	// is a random port opened by brower, netcat, etc.
	fmt.Printf("Get request from %s to %s.\n", c.RemoteAddr(), c.LocalAddr())
}

func main() {
	// Note, if port '0' is given to Listen, a random port will be used.
	listener, err := net.Listen("tcp", ":8080")
	fmt.Printf("Listening at: %v\n", listener.Addr())
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
