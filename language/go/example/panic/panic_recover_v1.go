package main

import "fmt"

func main() {
	defer func() {
		// The call to recover() works only if it's called directly in deferred function.
		fmt.Println("recovered:", recover())
	}()

	panic("not good")
}
