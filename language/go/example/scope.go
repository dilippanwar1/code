package main

import "fmt"

func main() {
	outer := "Foo"
	if true {
		inner := "Bar"
	}
	// Compile error: inner is undefined.
	fmt.Println(outer)
	fmt.Println(inner)
}
