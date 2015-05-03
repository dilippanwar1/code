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

func rangeClose() {
	queue := make(chan string, 2)
	queue <- "one"
	queue <- "two"
	close(queue)
	// This range iterates over each element as it’s received from queue. Because
	// we closed the channel above, the iteration terminates after receiving the
	// 2 elements. If we didn’t close it we’d block on a 3rd receive in the loop.
	for elem := range queue {
		fmt.Println(elem)
	}
}

func main() {
	cs := make(chan string)
	go makeCakeAndSend(cs, 5)
	go receiveCakeAndPack(cs)

	rangeClose()

	// Sleep for a while so that the program doesn’t exit immediately.
	time.Sleep(time.Second)
}
