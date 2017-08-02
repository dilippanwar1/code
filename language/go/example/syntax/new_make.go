package main

import "fmt"

func main() {
	// 'new' returns a zeroed value, equivalent to &{}
	// 'make' applies only to maps, slices and channels, and
	// does not return a pointer (return a value)
	var p *[]int = new([]int)     // allocates slice structure; *p == nil
	var v []int = make([]int, 10) // slice v refers to a new array of 10 int

	fmt.Println(p)
	fmt.Println(v)
	fmt.Println(v[0])
	// 'p' doesn't contain any value, so the following statement will panic
	// about index out of range.
	//   fmt.Println((*p)[0])
}
