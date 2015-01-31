package main

import (
	"crypto/tls"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"os/exec"
	"syscall"

	"github.com/docker/libchan"
	"github.com/docker/libchan/spdy"
)

// RemoteCommand is the received command parameters to execute locally and return
type RemoteCommand struct {
	Cmd        string
	Args       []string
	Stdin      io.Reader
	Stdout     io.WriteCloser
	Stderr     io.WriteCloser
	StatusChan libchan.Sender
}

// CommandResponse is the reponse struct to return to the client
type CommandResponse struct {
	Status int
}

func main() {
	cert := os.Getenv("TLS_CERT")
	key := os.Getenv("TLS_KEY")

	var listener net.Listener
	if cert != "" && key != "" {
		tlsCert, err := tls.LoadX509KeyPair(cert, key)
		if err != nil {
			log.Fatal(err)
		}

		tlsConfig := &tls.Config{
			InsecureSkipVerify: true,
			Certificates:       []tls.Certificate{tlsCert},
		}

		listener, err = tls.Listen("tcp", "localhost:9323", tlsConfig)
		if err != nil {
			log.Fatal(err)
		}
	} else {
		var err error
		listener, err = net.Listen("tcp", "localhost:9323")
		if err != nil {
			log.Fatal(err)
		}
	}

	// NewTransportListener is a warpper of net.Listener. It creates a net listener
	// and returns to caller.
	tl, err := spdy.NewTransportListener(listener, spdy.NoAuthenticator)
	if err != nil {
		log.Fatal(err)
	}

	for {
		// Block until a new connection is established, and create a new stream. For example,
		// when client call net.Dial("tcp", "127.0.0.1:9323"), this method will return. Apart
		// from calling net.Accept(), this method will also prepare spdy connection (i.e. call
		// spdystream.Serve().
		t, err := tl.AcceptTransport()
		if err != nil {
			log.Print(err)
			break
		}

		go func() {
			for {
				// When a new connection is made, i.e. client call net.Dial(), server blocks
				// here until client calls NewSendChannel().
				// In this go function, we have an established TCP connection, and server has
				// started backgroup spdy connection service. It is waiting for client to
				// create a new channel (stream) to exchange infomation.
				receiver, err := t.WaitReceiveChannel()
				if err != nil {
					log.Print(err)
					break
				}

				go func() {
					for {
						command := &RemoteCommand{}
						// When a new connection is made and a channel is established, i.e. client
						// call net.Dial(), and NewSendChannel(), server blocks here until client
						// call Send() on the channel.
						// So in this go function, we have an established TCP connection and channel,
						// and server is waiting for client to send information on the channel.
						err := receiver.Receive(command)
						fmt.Printf("Got %+v, %v\n", command, err)
						if err != nil {
							log.Print(err)
							break
						}

						cmd := exec.Command(command.Cmd, command.Args...)

						// This is redirect command output (cmd.Stdout) to command.Stdout.
						// command.Stdout is passed in from client; at runtime, it has type
						// spdy.byteStreamWrapper. When command write to its stdout, it is
						// then write to the stream.
						cmd.Stdout = command.Stdout
						cmd.Stderr = command.Stderr

						stdin, err := cmd.StdinPipe()
						if err != nil {
							log.Print(err)
							break
						}
						go func() {
							io.Copy(stdin, command.Stdin)
							stdin.Close()
						}()

						res := cmd.Run()
						command.Stdout.Close()
						command.Stderr.Close()

						// Compute exit status. 'res' from cmd.Run() implements error interface,
						// so we can't get an integer return status.
						returnResult := &CommandResponse{}
						if res != nil {
							if exiterr, ok := res.(*exec.ExitError); ok {
								returnResult.Status = exiterr.Sys().(syscall.WaitStatus).ExitStatus()
							} else {
								log.Print(res)
								returnResult.Status = 10
							}
						}

						err = command.StatusChan.Send(returnResult)
						if err != nil {
							log.Print(err)
						}
					}
				}()
			}
		}()
	}
}
