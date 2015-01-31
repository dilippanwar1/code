package main

import (
	"fmt"
	"net"
)

func main() {
	listener, _ := net.Listen("tcp", "127.0.0.1:8080")

	for {
		inConn, err := listener.Accept()
		if err != nil {
			fmt.Println("Accept failed: %v", err)
			continue
		}
		fmt.Println("Get connection.")

		// Use only CloseRead and CloseWrite won't close the socket.
		inTCPConn := inConn.(*net.TCPConn)
		inTCPConn.CloseRead()
		inTCPConn.CloseWrite()

		// inConn.Close()
	}
}
