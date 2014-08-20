package main

import "fmt"


func main() {

	// Create a new channel with make(chan val-type).  Channels are
	// typed by the values they convey.
	messages := make(chan string)

	// Send a value into channel using the 'channel <- ' syntax.
	go func() { messages <- "ping" } ()

	// Receive a value from channel using the '<- channel' syntax.
	// By default sends and receives block until both the sender
	// and receiver are ready.
	msg := <- messages
	fmt.Println(msg)
}
