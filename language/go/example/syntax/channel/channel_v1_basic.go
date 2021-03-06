package main

import "fmt"

func main() {
	// Create a new channel with make(chan val-type). Channels are
	// typed by the values they convey.
	messages := make(chan string)

	// Send a value into channel using the 'channel <- ' syntax.
	go func() { messages <- "ping" }()

	// Receive a value from channel using the '<- channel' syntax.
	// By default sends and receives block until both the sender
	// and receiver are ready.
	// The boolean variable ok returned by a receive operator indicates
	// whether the received value was sent on the channel (true) or is a
	// zero value returned because the channel is closed and empty (false).
	msg, ok := <-messages
	if ok {
		fmt.Println(msg)
	} else {
		fmt.Println("No message")
	}

	// Note: Only the sender should close a channel, never the receiver.
	// Sending on a closed channel will cause a panic.

	// Another note: Channels aren't like files; you don't usually need to
	// close them. Closing is only necessary when the receiver must be told
	// there are no more values coming, such as to terminate a range loop.
}
