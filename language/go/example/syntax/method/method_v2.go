package main

import (
	"fmt"
	"math"
)

type Rect struct {
	width  int
	height int
}

func (r *Rect) area() int {
	return r.width * r.height
}

func (r *Rect) perim() int {
	return 2 * (r.width + r.height)
}

type Circle struct {
	radius float32
}

func (c Circle) area() float32 {
	return math.Pi * c.radius * c.radius
}

func (c Circle) perim() float32 {
	return 2 * math.Pi * c.radius
}

func main() {
	r := Rect{width: 10, height: 5}
	fmt.Println("Area:", r.area())
	fmt.Println("Perim:", r.perim())

	rp := &r
	fmt.Println("Area:", rp.area())
	fmt.Println("Perim:", rp.perim())

	c := Circle{radius: 3}
	fmt.Println("Area:", c.area())
	fmt.Println("Perim:", c.perim())

	cp := &c
	fmt.Println("Area:", cp.area())
	fmt.Println("Perim:", cp.perim())
}
