package main

import "fmt"

type Rect struct {
	width  int
	height int
}

// This area method has a receiver type of *Rect, which means it supports the
// syntax: r.area(), where r is of type Rect or *Rect (Go will do the conversion).
// According to the spec, this method is the same as the function:
//   func area(r *Rect) int
func (r *Rect) area() int {
	return r.width * r.height
}

func (r *Rect) perim() int {
	return 2 * (r.width + r.height)
}

func main() {
	r := Rect{width: 10, height: 5}

	fmt.Println("Area:", r.area())
	fmt.Println("Perim:", r.perim())

	// Go automatically handles conversion between values and pointers for method
	// calls. You may want to use a pointer receiver type to avoid copying on
	// method calls or to allow the method to mutate the receiving struct. Note
	// that we can call area(), perim() on both r and &r, because r is addressable,
	// meaning that given r, Go is able to find the address of r, thus passing it
	// to the function.
	rp := &r
	fmt.Println("Area:", rp.area())
	fmt.Println("Perim:", rp.perim())
}
