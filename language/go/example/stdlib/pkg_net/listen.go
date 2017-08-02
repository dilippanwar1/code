package main

import (
	"fmt"
	"net"
)

func main() {
	// Basic1()
	// Basic2()
	// Basic3()
	Basic4()
}

func Basic1() {
	// net.Listen announces on the local network address with given type.
	listener, err := net.Listen("tcp4", "127.0.0.1:8080")
	if err != nil {
		fmt.Println("Error calling Listen[1]:", err)
		return
	}
	fmt.Printf("Listening at: %v\n", listener.Addr())
	// Block on listener until a connection is made by client, e.g.
	// $ telnet 127.0.0.1 8080
	conn, err := listener.Accept()
	if err != nil {
		fmt.Println("Error accepting[1]:", err)
		return
	}
	// E.g. Get request from 127.0.0.1:49711 to 127.0.0.1:8080; Here, port 49711
	// is a random port opened by telnet, browser, netcat, etc.
	fmt.Printf("Get request from %s to %s.\n", conn.RemoteAddr(), conn.LocalAddr())
	listener.Close()
}

func Basic2() {
	// Port is required, the 'laddr' parameter must be host:port pair. If port
	// '0' is given to Listen, a random port will be used.
	listener, err := net.Listen("tcp4", "127.0.0.1:0")
	if err != nil {
		fmt.Println("Error calling Listen[1]:", err)
		return
	}
	// E.g. Listening at: 127.0.0.1:42589
	fmt.Printf("Listening at: %v\n", listener.Addr())
	listener.Close()
}

func Basic3() {
	// Listen on tcp6.
	listener, err := net.Listen("tcp6", "[::1]:8080")
	if err != nil {
		fmt.Println("Error calling Listen[1]:", err)
		return
	}
	fmt.Printf("Listening at: %v\n", listener.Addr())
	// Block on listener until a connection is made by client. Here since we are
	// listening on ipv6, and it's not ipv4 mapped, making connection via 127.0.0.1
	// won't work, we need to do:
	// $ telnet ::1 8080
	conn, err := listener.Accept()
	if err != nil {
		fmt.Println("Error accepting[1]:", err)
		return
	}
	// Get request from [::1]:35350 to [::1]:8080.
	fmt.Printf("Get request from %s to %s.\n", conn.RemoteAddr(), conn.LocalAddr())
	listener.Close()
}

func Basic4() {
	// Listen on tcp, in which case both ipv4 and ipv6 will work.
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("Error calling Listen[1]:", err)
		return
	}
	fmt.Printf("Listening at: %v\n", listener.Addr())
	// Block on listener until a connection is made by client. Here we are
	// listening on tcp, and it's ipv4 mapped, making connection via 127.0.0.1
	// will work (as well as ::1), we can do:
	// $ telnet ::1 8080
	// or:
	// $ telnet 127.0.0.1 8080
	conn, err := listener.Accept()
	if err != nil {
		fmt.Println("Error accepting[1]:", err)
		return
	}
	// Get request from [::1]:35350 to [::1]:8080.
	fmt.Printf("Get request from %s to %s.\n", conn.RemoteAddr(), conn.LocalAddr())
	listener.Close()
}
