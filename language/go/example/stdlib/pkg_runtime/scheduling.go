package main

import (
	"fmt"
	"runtime"
)

func main() {
	done := false

	go func() {
		done = true
	}()

	for !done {
		// Allow other goroutine to run.
		runtime.Gosched()
	}
	fmt.Println("done!")
}
