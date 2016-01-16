package main

import "fmt"

type data struct {
	name string
}

func main() {
	m := map[string]data{"x": {"one"}}
	// It doesn't work because map elements are not addressable.
	//   m["x"].name = "two"

	// Workaround: assign a new value since map key is addressable.
	r := m["x"]
	r.name = "two"
	m["x"] = r
	fmt.Printf("%v\n", m)

	// Workaround: use map of pointer.
	m1 := map[string]*data{"x": {"one"}}
	m1["x"].name = "two"
	fmt.Printf("%v\n", m)
	// But be careful not to access nil pointer.
	//   m1["z"].name = "what?"
	fmt.Println(m1["z"])
}
