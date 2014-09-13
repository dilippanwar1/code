/* UDPDaytimeServer */
package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

func main() {

	service := ":1200"
	udpAddr, err := net.ResolveUDPAddr("udp4", service)
	fmt.Println(udpAddr)
	checkError(err)

	conn, err := net.ListenUDP("udp", udpAddr)
	checkError(err)

	for {
		handleClient(conn)
	}
}

func handleClient(conn *net.UDPConn) {

	var buf [512]byte

	// Block until client connection. Note that conn.ReadFromUDP() accepts
	// a slice as argument, passing buf directly will cause error, using
	// buf[0:] or buf[:] will convert array buf to a slice.
	_, addr, err := conn.ReadFromUDP(buf[0:])
	if err != nil {
		return
	}
	fmt.Println("Received:", string(buf[:]))

	daytime := time.Now().String()

	conn.WriteToUDP([]byte(daytime), addr)
}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error ", err.Error())
		os.Exit(1)
	}
}
