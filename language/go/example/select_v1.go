package main

import (
	"fmt"
	"time"
)

func Test1() {
	ticker1 := time.Tick(2 * time.Second)
	ticker2 := time.Tick(3 * time.Second)
	for {
		// 1. select will wait until one of the cases is true
		// 2. only one case will be executed (there is no fall through)
		select {
		case <-ticker1:
			fmt.Println("Hello Here!")
		case <-ticker2:
			fmt.Println("Hello There!")
		}
	}
}

func Test2() {
	ticker1 := time.Tick(2 * time.Second)
	ticker2 := time.Tick(3 * time.Second)
	for {
		// 3. 'default' will be executed if no case matches; in this case
		// there will be a lot of 'Spam'.
		select {
		case <-ticker1:
			fmt.Println("Hello Here!")
		case <-ticker2:
			fmt.Println("Hello There!")
		default:
			fmt.Println("Spam")
		}
	}
}

func main() {
	Test1()
}
