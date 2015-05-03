package main

import (
	"fmt"
	"math/rand"
	"time"
)

func boring(msg string, quit chan bool) <-chan string {
	c := make(chan string)
	go func() {
		for i := 0; i < 5; i++ {
			select {
			case c <- fmt.Sprintf("%s %d", msg, i):
			case <-quit:
				fmt.Println("Quit")
				// cleanup
				quit <- true
				return
			}
			time.Sleep(time.Duration(rand.Intn(100)) * time.Millisecond)
		}
	}()
	return c
}
func main() {
	quit := make(chan bool)
	c := boring("Ann", quit)
	for i := 0; i < 2; i++ {
		fmt.Printf("You say: %q\n", <-c)
	}
	quit <- true
	<-quit
}
