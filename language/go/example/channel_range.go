// Receivers of data have a problem of knowing when to stop waiting for data.
// Go provides the range keyword which when used with a channel will wait on
// the channel until it is closed.

package main

import (
	"fmt"
	"strconv"
	"time"
)

func makeCakeAndSend(cs chan string, count int) {
	for i := 1; i <= count; i++ {
		cakeName := "Strawberry Cake " + strconv.Itoa(i)
		cs <- cakeName
	}
	close(cs)
}

func receiveCakeAndPack(cs chan string) {
	for s := range cs {
		fmt.Println("Packing received cake: ", s)
	}
}

func main() {
	cs := make(chan string)
	go makeCakeAndSend(cs, 5)
	go receiveCakeAndPack(cs)

	// Sleep for a while so that the program doesn’t exit immediately.
	time.Sleep(time.Second)
}
