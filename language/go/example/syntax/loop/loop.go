package main

import "fmt"

func mergeResults(rs []int, added []int) []int {
	for _, r := range added {
		found := false
		for i := range rs {
			if rs[i] == r {
				found = true
				break
			}
		}
		if !found {
			rs = append(rs, r)
		}
	}
	return rs
}

func main() {
	// It's possible to modify slice in place.
	slice := []int{1, 2, 3, 4, 5}
	for i := range slice {
		if slice[i] == 4 {
			slice = append(slice, slice[i])
		}
	}
	fmt.Println(slice) // output: [1 2 3 4 5 4]

	slice1 := []int{1, 2, 3, 4, 5}
	slice2 := []int{4, 5, 6, 7, 8}
	fmt.Println(mergeResults(slice1, slice2)) // [1 2 3 4 5 6 7 8]
	fmt.Println(slice1)
	fmt.Println(slice2)

	// Print:
	//  [0 1 1]
	//  [0 1 1 2]
	ints := []int{0, 1}
	for i := range ints {
		ints = append(ints, i+1)
		fmt.Println("Array ints:", ints)
	}
}
