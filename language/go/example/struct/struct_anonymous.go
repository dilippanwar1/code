package main

import "fmt"

type Kitchen struct {
	numOfPlates int
	numOfLamps  int
}

type House struct {
	Kitchen    // anonymous field
	numOfRooms int
	numOfLamps int
}

func main() {
	// To initialize, we have to use composed type name.
	h := House{Kitchen{10, 1}, 3, 5}
	fmt.Println(h)

	// Access numOfRomms as usual.
	fmt.Println("House h has rooms:", h.numOfRooms)

	// Because numOfPlates is a field of anonymous field Kitchen, so it
	// can be referred to like a field of House. If Kitchen is not an
	// anonymous field, then this won't work.
	fmt.Println("House h has plates:", h.numOfPlates)

	// We can refer to the embedded struct in its entirety by referring
	// to the name of the struct type.
	fmt.Println("The Kitchen contents of this house:", h.Kitchen)

	// The anonymous field is still available to be accessed by its type name.
	fmt.Println("Access The Kitchen contents:", h.Kitchen.numOfPlates)

	// When conflict, variable appears at higher level take precedence.
	// There is no rules if variables are at the same level; Go compiler
	// will generate error in this case.
	fmt.Println("House h has lamps:", h.numOfLamps)

	// We can still get numOfLamps from Kitchen.
	fmt.Println("Access The Kitchen contents:", h.Kitchen.numOfLamps)
}
