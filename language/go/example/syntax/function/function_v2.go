package main

import "fmt"

func appendToSlice(a []int) {
	a = append(a, 0)
}

func changeArray(a [3]int) {
	a[0] = 111
}

func changeSlice(a []int) {
	a[0] = 111
}

func main() {
	// Note that unlike C/C++, array is pass by value. So
	// the function will get a copy of the array.
	array := [3]int{1, 2, 3}
	changeArray(array)
	fmt.Println(array) // [1 2 3]

	// slice, on the other hand, is pass by reference.
	slice := []int{1, 2, 3}
	changeSlice(slice)
	fmt.Println(slice) // [111 2 3]

	// This appendToSlice will not change slice, not because the
	// slice parameter is copied, but the 'append' method in the
	// method will make a copy of the slice.
	appendToSlice(slice)
	fmt.Println(slice) // [111 2 3]
}
