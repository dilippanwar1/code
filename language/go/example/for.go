// for loop is Go's only looping construct.

package main

import "fmt"


func main() {

	// Basic type 1:
	i := 1
	for i <= 3 {
		fmt.Println(i)
		i = i + 1
	}

	// Basic type 2:
	for j := 7; j <= 9; j++ {
		fmt.Println(i)
	}

	// Baisc type 3: Infinite loop.
	for {
		fmt.Println("Loop")
		break;
	}
}
