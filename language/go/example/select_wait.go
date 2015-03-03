// Go’s select lets you wait on multiple channel operations. Combining
// goroutines and channels with select is a powerful feature of Go.
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
	// After waits for the duration to elapse and then sends the
	// current time on the returned channel.
	for i := 0; i < 10; i++ {
		select {
		case msg1 := <-c1:
			fmt.Println("received", msg1)
		case msg2 := <-c2:
			fmt.Println("received", msg2)
		case <-time.After(time.Millisecond * 500):
			fmt.Println("waiting")
		}
	}
}
