package main

import (
	"fmt"
	"strconv"
	"time"
)

func makeCakeAndSend(cs chan string, flavor string, count int) {
	for i := 1; i <= count; i++ {
		cakeName := flavor + " Cake " + strconv.Itoa(i)
		cs <- cakeName
	}
	close(cs)
}

func receiveCakeAndPack(strbry_cs chan string, choco_cs chan string) {
	strbry_closed, choco_closed := false, false

	for {
		// If both channels are closed then we can stop.
		if strbry_closed && choco_closed {
			fmt.Println("Both channels closed.")
			return
		}
		select {
		case cakeName, strbry_ok := <-strbry_cs:
			if !strbry_ok {
				strbry_closed = true
			} else {
				fmt.Println("Received from Strawberry channel.  Now packing", cakeName)
			}
		case cakeName, choco_ok := <-choco_cs:
			if !choco_ok {
				choco_closed = true
			} else {
				fmt.Println("Received from Chocolate channel.  Now packing", cakeName)
			}
		}
	}
}

func main() {
	strbry_cs := make(chan string)
	choco_cs := make(chan string)

	// Two cake makers
	go makeCakeAndSend(choco_cs, "Chocolate", 3)
	go makeCakeAndSend(strbry_cs, "Strawberry", 3)

	// Pack all cakes received on these cake channels.
	go receiveCakeAndPack(strbry_cs, choco_cs)

	// Sleep for a while so that the program doesn’t exit immediately
	time.Sleep(2 * time.Second)
}
