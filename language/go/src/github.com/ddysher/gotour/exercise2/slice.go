// Slices: Implement Pic. It should return a slice of length dy,
// each element of which is a slice of dx 8-bit unsigned integers.

package main

import "code.google.com/p/go-tour/pic"

func Pic(dx, dy int) [][]uint8 {
	// 'make' declaration: make([]T, length, capacity)
	result := make([][]uint8, dx)
	for x := 0; x < dx; x++ {
		result[x] = make([]uint8, dy)
		for y := 0; y < dy; y++ {
			result[x][y] = uint8((x+y)/2)
		}
	}
	return result
}

func main() {
	pic.Show(Pic)
}
