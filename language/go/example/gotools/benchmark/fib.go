package main

import "fmt"

// Fib computes the n'th number in the Fibonacci series.
func Fib(n int) int {
	if n < 2 {
		return n
	}
	return Fib(n-1) + Fib(n-2)
}

func main() {
	fmt.Println(Fib(4))
}
