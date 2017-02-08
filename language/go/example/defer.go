// A defer statement pushes a function call onto a list. The list of saved
// calls is executed after the surrounding function returns. Defer is commonly
// used to simplify functions that perform various clean-up actions.

package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	a()
	b()
	fmt.Println()
	fmt.Println(c())
	d()
	DeferHelloWorld()
}

// The behavior of defer statements is straightforward and predictable.
// There are three simple rules:
// 1. A deferred function's arguments are evaluated when the defer statement
//  is evaluated. In this example, the expression "i" is evaluated when the
//  Println call is deferred. The deferred call will print "0" after the
//  function returns.
func a() {
	i := 0
	defer fmt.Println(i) // Print 0
	i++                  // Will not affect defer's argument value
	return
}

// 2. Deferred function calls are executed in 'Last In First Out' order after
//  the surrounding function returns.
func b() {
	// Prints "3210":
	for i := 0; i < 4; i++ {
		defer fmt.Print(i)
	}
}

// 3. Deferred functions may read and assign to the returning function's named
//  return values. In this example, a deferred function increments the return
//  value i after the surrounding function returns. Thus, this function returns
//  returns 2. This is convenient for modifying the error return value of a
//  function.
func c() (i int) {
	defer func() { i++ }() // Print 2
	return 1
}

// Note, deferred function's argument is evaluated when the defer statement is
// evaluated, but function body is not evaluated.
func d() {
	success := false
	defer func() { fmt.Println(success) }() // Print 'true'
	success = true
}

func CopyFile(dstName, srcName string) (written int64, err error) {
	src, err := os.Open(srcName)
	if err != nil {
		return
	}
	// By using defer, we are sure src file is always closed.
	defer src.Close()

	dst, err := os.Create(dstName)
	if err != nil {
		return
	}
	defer dst.Close()

	return io.Copy(dst, src)
}

type WorldPrinter struct{}

func (wp *WorldPrinter) PrintWorld() {
	fmt.Printf("World ")
}

func PrintHello() interface {
	PrintWorld()
} {
	fmt.Printf("Hello ")
	return &WorldPrinter{}
}

// 'Hello' is printed at first since it is evaluated at function execution
// time; then it follows rule 2, i.e. LIFO order. The function output is:
//   Hello XYZ World ABC
func DeferHelloWorld() {
	defer fmt.Printf("ABC ")
	defer PrintHello().PrintWorld()
	defer fmt.Printf("XYZ ")
}
