package main

import "fmt"


func plus(a int, b int) int {
	return a + b
}

func vals() (int, int) {
	return 3, 7
}


func main() {

	res := plus(3, 5)
	fmt.Println(res)

	// Return multiple value.
	a, b := vals()
	fmt.Println(a)
	fmt.Println(b)

	// Value can be ignored by '_'.
	c, _ := vals()
	fmt.Println(c)
}
