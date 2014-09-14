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
		inConn.Close()
	}
}
