// +build main1

// Build tags allows compile time file inclusion. Building in the directory
// will give error that main has been redeclared. To use build tag, do:
//  go build -tags 'main1'
package main

import (
	"fmt"
)

func main() {
	fmt.Println("This is main 1")
}
