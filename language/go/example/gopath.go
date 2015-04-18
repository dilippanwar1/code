// This demonstrates that as long as GOPATH is properly set, we can import
// the right packages no matter where it is called.
//
// Open a new terminal (where GOPATH is set to somewhere else), command
// 'go run hello_pkg.go' will fail due to missing package.  But if we source
// ../build.sh, where GOPATH is set to parent directory, then we can run it.

package main

import (
	"fmt"

	"github.com/ddysher/newmath"
)

func main() {
	fmt.Printf("Hello, world. I'm GO!\n")
	fmt.Printf("Hello, world. Sqrt(2) = %v\n", newmath.Sqrt(2))
}
