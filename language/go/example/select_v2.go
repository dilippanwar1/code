// Go’s select lets you wait on multiple channel operations. Combining
// goroutines and channels with select is a powerful feature of Go. A
// select blocks until one of its cases can run, then it executes that
// case. It chooses one at random if multiple are ready.
package main

import (
	"fmt"
	"time"
)

func main() {

	c1 := make(chan string)
	c2 := make(chan string)

	// Each channel will receive a value after some amount of time.
	go func() {
		time.Sleep(time.Second * 1)
		c1 <- "one"
	}()

	go func() {
		time.Sleep(time.Second * 2)
		c1 <- "two"
	}()

	// Use select to wait both of these values simultaneously.
	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-c1:
			fmt.Println("received", msg1)
		case msg2 := <-c2:
			fmt.Println("received", msg2)
		}
	}
}
