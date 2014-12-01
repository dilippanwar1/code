// Package newmath is a trivial example package.
package newmath

import "fmt"

func init() {
	fmt.Println("I will be ran as long as anyone imports me.")
}

// Sqrt returns an approximation to the square root of x.
func Sqrt(x float64) float64 {
	z := 1.0
	for i := 0; i < 1000; i++ {
		z -= (z*z - x) / (2 * z)
	}
	return z
}
