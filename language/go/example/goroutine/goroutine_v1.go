package main

import "fmt"

func sayWorld() {
	fmt.Println("World")
}

// Note go runtime will NOT make sure all goroutines finished before exit.
// In this example, the program will only print "Hello" (although it's
// possible to print "Hello World" if sayWorld is scheduled immediately
// after fmt.Println("Hello"), but this is very unlikely.
func main() {
	fmt.Println("Hello")
	go sayWorld()
}
