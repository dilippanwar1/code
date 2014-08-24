package main

import "fmt"

// The final parameter in a function signature may have a type prefixed
// with .... A function with such a parameter is called variadic and may
// be invoked with zero or more arguments for that parameter.
func sum(num int, items ...int) int {
	total := 0
	for i := 0; i < num; i++ {
		total += items[i]
	}
	return total
}

func main() {
	fmt.Println(sum(5, 1, 2, 3, 4, 5))
}
