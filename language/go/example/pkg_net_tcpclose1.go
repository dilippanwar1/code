package main

import (
	"fmt"
	"io"
	"net"
)

func main() {
	listener, _ := net.Listen("tcp", "127.0.0.1:8000")

	for {
		inConn, err := listener.Accept()
		if err != nil {
			fmt.Println("Accept failed: %v", err)
			continue
		}
		outConn, err := net.Dial("tcp", "127.0.0.1:8080")
		if err != nil {
			fmt.Println("Dial failed: %v", err)
			inConn.Close()
			continue
		}

		fmt.Println("-------------In", inConn,
			"Local", inConn.LocalAddr(), "Remote", inConn.RemoteAddr())
		fmt.Println("------------Out", outConn,
			"Local", outConn.LocalAddr(), "Remote", outConn.RemoteAddr())
		proxyTCP(inConn.(*net.TCPConn), outConn.(*net.TCPConn))
	}
}

func proxyTCP(in, out *net.TCPConn) {
	fmt.Println("Creating proxy between %v <-> %v <-> %v <-> %v",
		in.RemoteAddr(), in.LocalAddr(), out.LocalAddr(), out.RemoteAddr())
	go copyBytes(in, out)
	go copyBytes(out, in)
	// time.Sleep(2 * time.Second)
	// in.Close()
	// out.Close()
}

func copyBytes(in, out *net.TCPConn) {
	fmt.Println("Copying from %v <-> %v <-> %v <-> %v",
		in.RemoteAddr(), in.LocalAddr(), out.LocalAddr(), out.RemoteAddr())
	if _, err := io.Copy(in, out); err != nil {
		fmt.Println("I/O error: %v", err)
	}
	fmt.Println(in, "Close Read", in.CloseRead())
	fmt.Println(out, "Close Write", out.CloseWrite())
}
