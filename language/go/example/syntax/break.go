// Breaking Out of "for switch" and "for select" Code Blocks
//
// A "break" statement without a label only gets you out of the inner switch/select
// block. If using a "return" statement is not an option then defining a label for
// the outer loop is the next best thing.
package main

import "fmt"

func main() {
loop:
	for {
		switch {
		case true:
			fmt.Println("breaking out...")
			break loop
		}
	}

	fmt.Println("out!")
}
