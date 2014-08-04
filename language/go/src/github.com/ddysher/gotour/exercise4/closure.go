// Function and closure.
package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	current := 1
	previous := 0
	return func() int {
		temp := previous + current
		previous = current
		current = temp
		return temp
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
