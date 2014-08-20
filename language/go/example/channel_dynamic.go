package main

import "fmt"


func main() {

	// A channel that can send/receive 'anything'.
	messages := make(chan interface{})

	go func() { messages <- "ping" } ()
	fmt.Println(<- messages)

	go func() { messages <- 4.1416 } ()
	fmt.Println(<- messages)
}
