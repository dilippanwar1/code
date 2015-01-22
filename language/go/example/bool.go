package main

import "fmt"

func main() {
	fmt.Println(isValid("abc", 20))
	fmt.Println(isValid("abc", 16))
	fmt.Println(isValid("xxx", 20))
}

func isValid(name string, age int) bool {
	return name != "xxx" && age > 18
}
