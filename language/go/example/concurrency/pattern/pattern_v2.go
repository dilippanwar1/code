package main

import (
	"fmt"
	"math/rand"
	"time"
)

func boring(msg string) <-chan string {
	c := make(chan string)
	go func() {
		for i := 0; i < 5; i++ {
			c <- fmt.Sprintf("%s %d", msg, i)
			time.Sleep(time.Duration(rand.Intn(100)) * time.Millisecond)
		}
	}()
	return c
}

func WrongWay() {
	ann := boring("Ann")
	joe := boring("Joe")
	for i := 0; i < 5; i++ {
		// Ann or Joe will be blocked if the other doesn't finish, we need
		// multiplexing, also called fan-in, merging, etc.
		fmt.Printf("Ann: %q\n", <-ann)
		fmt.Printf("Joe: %q\n", <-joe)
	}
	fmt.Println("You're boring; I'm leaving.")
}

func PatternWay() {
	c := fanIn2(boring("Ann"), boring("Joe"))
	for i := 0; i < 10; i++ {
		fmt.Printf("You say: %q\n", <-c)
	}
	fmt.Println("You're boring; I'm leaving.")
}

func fanIn1(ch1, ch2 <-chan string) <-chan string {
	c := make(chan string)
	// Recive from ch1, ch2 forever.
	go func() {
		for {
			c <- <-ch1
		}
	}()
	go func() {
		for {
			c <- <-ch2
		}
	}()
	return c
}

func fanIn2(ch1, ch2 <-chan string) <-chan string {
	c := make(chan string)
	go func() {
		for {
			select {
			case s := <-ch1:
				c <- s
			case s := <-ch2:
				c <- s
			}
		}
	}()
	return c
}

func main() {
	PatternWay()
}
