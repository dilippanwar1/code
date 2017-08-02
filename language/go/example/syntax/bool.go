package main

import "fmt"

func main() {
	fmt.Println(isValid("abc", 20)) // true
	fmt.Println(isValid("abc", 16)) // false
	fmt.Println(isValid("xxx", 20)) // false

	// Pointer to bool.
	var boolp *bool
	true_var := true
	boolp = &true_var
	fmt.Println(*boolp)
}

func isValid(name string, age int) bool {
	return name != "xxx" && age > 18
}
