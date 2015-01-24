// The Dial function connects to a server.

package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
)

func main() {
	conn, err := net.Dial("tcp", "google.com:80")
	if err != nil {
		fmt.Println("Error dailing to google.com:80")
		os.Exit(1)
	}
	fmt.Fprintf(conn, "GET / HTTP/1.0\r\n\r\n")
	status, err := bufio.NewReader(conn).ReadString('\n')
	fmt.Printf(status)

	// E.g. From 74.125.226.4:80 to 10.0.0.5:49950.
	fmt.Printf("From %s to %s.\n", conn.RemoteAddr(), conn.LocalAddr())
}
