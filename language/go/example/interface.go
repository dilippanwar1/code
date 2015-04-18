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

// Define two dummy values and discard them. This is usually used as a
// static (compile time) check that implementation satifies interface.
// Here, we check that Square and Circle type implements Geometry interface.
var _ Geometry = Square{}
var _ Geometry = Circle{}

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
	underlying, ok := geo.(Square)
	if ok {
		fmt.Println("get square", underlying)
	}
	fmt.Println(geo)
	fmt.Println(geo.Area())
	fmt.Println(geo.Perim())
}

func nilInterface(geo Geometry) {
	if geo == nil {
		fmt.Println("geo is nil")
	} else {
		fmt.Println("geo is not nil")
	}
}

func main() {
	s := Square{width: 3, height: 4}
	c := Circle{radius: 5}

	measure(s)
	measure(c)

	nilInterface(nil)
}
