// Program starts from main package.
// Go command executables are statically linked; the package objects
// need not be present to run Go programs.
package main

import (
	"fmt"
	"github.com/ddysher/newmath"
)

func main() {
	fmt.Printf("Hello, world. I'm GO!\n")
	fmt.Printf("Hello, world. Sqrt(2) = %v\n", newmath.Sqrt(2))
}
