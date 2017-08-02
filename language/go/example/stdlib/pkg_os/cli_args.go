package main

import (
	"fmt"
	"os"
)

func main() {
	// `os.Args` provides access to raw command-line arguments. Note that the
	// first value in this slice is the path to the program, and 'os.Args[1:]'
	// holds the arguments to the program.
	argsWithProg := os.Args
	argsWithoutProg := os.Args[1:]

	// You can get individual args with normal indexing.
	arg := os.Args[3]

	// $ go run cli_args.go 1 2 3 4
	fmt.Println(argsWithProg)    // [/tmp/go-build518490069/command-line-arguments/_obj/exe/cli_args 1 2 3 4]
	fmt.Println(argsWithoutProg) // [1 2 3 4]
	fmt.Println(arg)             // 3
}
