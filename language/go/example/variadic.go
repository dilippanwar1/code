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

func fn(args ...string) {
	fmt.Println(args[0])
	fmt.Println(args[1])
	fmt.Printf("The whole slice: %v\n", args)
}

func main() {
	fmt.Println(sum(5, 1, 2, 3, 4, 5))
	fmt.Println("--")
	fn("Hey", "there")
	fmt.Println("--")
	slice := []string{"Hello", "to", "you", "too"}
	// When calling a function, if there are several arguments in a slice, it
	// will unpack them and pass as separate arguments to a variadic function.
	fn(slice...)
}
