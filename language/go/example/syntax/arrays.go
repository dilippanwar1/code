// https://blog.golang.org/go-slices-usage-and-internals
//
// Points about Go's array:
// - An array's size is fixed; its length is part of its type ([4]int and
//   [5]int are distinct, incompatible types).
// - The in-memory representation of [4]int is just four integer values laid
//   out sequentially.
// - Go's arrays are values. An array variable denotes the entire array; it
//   is not a pointer to the first array element (as would be the case in C).
//   This means that when you assign or pass around an array value you will
//   make a copy of its contents. (To avoid the copy you could pass a pointer
//   to the array, but then that's a pointer to an array, not an array.) One
//   way to think about arrays is as a sort of struct but with indexed rather
//   than named fields: a fixed-size composite value.
package main

import "fmt"

func main() {
	// Here we create an array a that will hold exactly 5 ints. The type of
	// elements and length are both part of the array’s type, so arrays can't
	// be resized. By default an array is zero-valued, which for ints means 0s.
	var a [5]int
	fmt.Println("emp:", a)

	// We can set a value at an index using the array[index] = value syntax,
	// and get a value with array[index].
	a[4] = 100
	fmt.Println("set:", a)
	fmt.Println("get:", a[4])

	// The builtin len returns the length of an array.
	fmt.Println("len:", len(a))

	// Use this syntax to declare and initialize an array in one line. Note
	// [n]T is an array of n values type T, and []T is a slice of type T.
	b := [5]int{1, 2, 3, 4, 5}
	fmt.Println("dcl:", b)

	// This is also an array ([...] = array vs [] = slice). Use '...' to have
	// compiler calculate the length.
	c := [...]int{1, 2, 3, 4, 5}
	fmt.Println("ccc:", c)

	// Array types are one-dimensional, but you can compose types to build
	// multi-dimensional data structures.
	var twoD [2][3]int
	for i := 0; i < 2; i++ {
		for j := 0; j < 3; j++ {
			twoD[i][j] = i + j
		}
	}
	fmt.Println("2d:", twoD)
}