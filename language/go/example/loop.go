package main

import "fmt"

func main() {
	array := []int{1, 2, 3, 4, 5}
	for i := range array {
		if array[i] == 4 {
			array = append(array, array[i])
		}
	}
	fmt.Println(array)

	array1 := []int{1, 2, 3, 4, 5}
	array2 := []int{4, 5, 6, 7, 8}
	fmt.Println(mergeResults(array1, array2))
}

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
