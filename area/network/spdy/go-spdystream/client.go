package main

import (
	"fmt"
	"net"
	"net/http"

	"github.com/docker/spdystream"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:8080")
	if err != nil {
		panic(err)
	}
	// Like server, this creates a new spdy connection. In spdy protocal, both
	// server and client need open a connection.
	spdyConn, err := spdystream.NewConnection(conn, false)
	if err != nil {
		panic(err)
	}
	// Serve starts a background service to parse spdy protocal. Also, both
	// server and client need to call the Serve.
	go spdyConn.Serve(spdystream.NoOpStreamHandler)

	// Client initiates a new stream.
	stream, err := spdyConn.CreateStream(http.Header{}, nil, false)
	if err != nil {
		panic(err)
	}
	stream.Wait()

	// Write to the stream and get response.
	fmt.Fprint(stream, "Writing to stream")
	stream.Write([]byte("abc"))
	buf := make([]byte, 25)
	stream.Read(buf)
	fmt.Println(string(buf))

	fmt.Println(stream.Close())
	fmt.Println(spdyConn.Close())
	fmt.Println(conn.Close())
}
