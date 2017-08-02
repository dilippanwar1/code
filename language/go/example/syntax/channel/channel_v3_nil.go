package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	var a chan string
	var b chan string
	rand.Seed(time.Now().Unix())
	if rand.Intn(2) == 0 {
		a = nil
		b = make(chan string)
		fmt.Println("nil a")
	} else {
		a = make(chan string)
		b = nil
		fmt.Println("nil b")
	}

	// Sends and receives on nil channels will be blocked.
	go func() { a <- "a" }()
	go func() { b <- "b" }()

	// Select never selects a blocking case.
	select {
	case s := <-a:
		fmt.Println(s)
	case s := <-b:
		fmt.Println(s)
	}
}
