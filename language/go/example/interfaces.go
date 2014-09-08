// Interfaces are named collections of method signatures. This is a core
// concept in Go’s type system; instead of designing our abstractions in
// terms of what kind of data our types can hold, we design our abstractions
// in terms of what actions our types can execute.

package main

import "fmt"
import "math"

type Geometry interface {
	Area() float64
	Perim() float64
}

type Square struct {
	width  float64
	height float64
}

type Circle struct {
	radius float64
}

// To implement an interface in Go, we just need to implement all the methods
// in the interface. Here we implement Geometry on Square and Circle.
func (s Square) Area() float64 {
	return s.width * s.height
}

func (s Square) Perim() float64 {
	return 2 * (s.width + s.height)
}

func (c Circle) Area() float64 {
	return math.Pi * c.radius * c.radius
}

func (c Circle) Perim() float64 {
	return 2 * math.Pi * c.radius
}

// If a variable has an interface type, i.e. geo, then we can call methods
// that are in the named interface.
func measure(geo Geometry) {
	fmt.Println(geo)
	fmt.Println(geo.Area())
	fmt.Println(geo.Perim())
}

func main() {

	s := Square{width: 3, height: 4}
	c := Circle{radius: 5}

	measure(s)
	measure(c)
}
