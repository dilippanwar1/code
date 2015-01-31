package main

import (
	"net"

	"github.com/docker/spdystream"
)

func main() {
	// Create a base TCP connection. Calling listen() on a socket causes the
	// kernel's tcp/ip implementation to begin accepting connections sent to
	// the socket's bound name (port). This will happen whether or not you
	// ever call accept().  accept() simply gives your server a way to access
	// and interact with the client sockets that have connected to your listening
	// socket.
	listener, err := net.Listen("tcp", "localhost:8080")
	if err != nil {
		panic(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			panic(err)
		}
		// NewConnection creates a new spdy connection from an existing network connection.
		// spdy uses existing TCP connection, and multiplex the connection with streams.
		// E.g. a client request 2 images. For HTTP, client opens two TCP connections and
		// wait for responses (up to 6 connections). For spdy, only one connection is
		// made. The connection is multiplexed to send the two images. A stream represents
		// one image, control information and data frame flow in the stream. Each stream
		// has a unique ID.
		spdyConn, err := spdystream.NewConnection(conn, true)
		if err != nil {
			panic(err)
		}
		// Serve starts a background service to parse spdy protocal. Both server and client
		// need to call this; otherwise, streams cannot be parsed.
		go spdyConn.Serve(spdystream.MirrorStreamHandler)
	}
}
