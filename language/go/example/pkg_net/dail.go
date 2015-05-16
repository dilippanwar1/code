package main

import (
	"bufio"
	"fmt"
	"net"
)

func main() {
	// Dial is a low-level function used to connect to a server. After calling
	// dail in client, server's Accept() will return and a new connection is
	// established.
	conn, err := net.Dial("tcp", "127.0.0.1:8080")
	if err != nil {
		fmt.Printf("Error calling dail: %v", err)
		return
	}
	fmt.Fprintf(conn, "GET / HTTP/1.0\r\n\r\n")
	status, err := bufio.NewReader(conn).ReadString('\n')
	fmt.Printf(status)

	// E.g. From 74.125.226.4:80 to 10.0.0.5:49950
	fmt.Printf("From %s to %s\n", conn.RemoteAddr(), conn.LocalAddr())
}
