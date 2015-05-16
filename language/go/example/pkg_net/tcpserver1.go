package main

import (
	"fmt"
	"net"
)

func main() {
	listener, _ := net.Listen("tcp", "127.0.0.1:8080")

	for {
		// Block until a new connection from client, e.g. client call
		// net.Dail().
		inConn, err := listener.Accept()
		if err != nil {
			fmt.Println("Accept failed: %v", err)
			continue
		}
		fmt.Println("Get connection.")

		// Convert to TCPConn as we listen on tcp connection above.
		// TCPConn is an implementation of the Conn interface for TCP
		// network connections.
		inTCPConn := inConn.(*net.TCPConn)
		// Use only CloseRead or CloseWrite won't close the socket, we
		// need to close both side, or use Close instead.
		if true {
			inTCPConn.CloseRead()
			inTCPConn.CloseWrite()
		} else {
			inConn.Close()
		}
	}
}
