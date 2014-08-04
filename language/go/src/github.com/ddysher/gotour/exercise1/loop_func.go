// Loops and Functions

package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) float64 {
	z := 1.0
	// Same as C/Java, but without ().
	for i := 0; i < 10; i++ {
		z = z - (z*z - x) / 2 / z;
	}
	return z
}

func Sqrt2(x float64) float64 {
	z := 1.0
	pre := x
	for {
		z = z - (z*z - x) / 2 / z;
		if math.Abs(z - pre) < 0.0001 {
			break
		}
		pre = z
	}
	return z
}

func main() {
	fmt.Println(Sqrt2(2))
}
