// This demonstrates that as long as GOPATH is properly set, we can import
// the right packages no matter where it is called.

package main

import (
	"fmt"
	"github.com/ddysher/newmath"
)

func main() {
	fmt.Printf("Hello, world. I'm GO!\n")
	fmt.Printf("Hello, world. Sqrt(2) = %v\n", newmath.Sqrt(2))
}
