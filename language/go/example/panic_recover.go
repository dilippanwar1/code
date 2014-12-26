// When panic is called, including implicitly for run-time errors such as
// indexing a slice out of bounds or failing a type assertion, it immediately
// stops execution of the current function and begins unwinding the stack
// of the goroutine, running any deferred functions along the way. If that
// unwinding reaches the top of the goroutine's stack, the program dies.
// However, it is possible to use the built-in function recover to regain
// control of the goroutine and resume normal execution.
//
// A call to recover stops the unwinding and returns the argument passed to
// panic. Because the only code that runs while unwinding is inside deferred
// functions, recover is only useful inside deferred functions.

package main

import "fmt"

func main() {
	f()
	fmt.Println("Returned normally from f.")
}

func f() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Recovered in f", r)
		}
	}()
	fmt.Println("Calling g.")
	g(0)
	fmt.Println("Returned normally from g.")
}

func g(i int) {
	if i > 3 {
		fmt.Println("Panicking!")
		panic(fmt.Sprintf("%v", i))
	}
	defer fmt.Println("Defer in g", i)
	fmt.Println("Printing in g", i)
	g(i + 1)
}
