package main

import "fmt"

func main() {

	// Constructor 1:
	// Use builtin make to create a map: make(map[key-type]val-type).
	m := make(map[string]int)

	m["k1"] = 7
	m["k2"] = 13

	fmt.Println("Craated map:", m)
	fmt.Println("Get key k1:", m["k1"])
	fmt.Println("Map length:", len(m))

	// Use builtin delete to delete a key (provide the key val).
	delete(m, "k2")
	fmt.Println("Deleted k2:", m)

	// 'delete' is no-op if there is no such element.
	delete(m, "k3")

	// The optional second return value when getting a value from a map indicates
	// if the key presents in the map. This can be used to disambiguate between
	// missing keys and keys with zero values like 0 or "".  Here, present will be
	// false, but _ is still 0.
	_, present := m["k2"]
	fmt.Println("k2 present:", present)

	// Constructor 2:
	// Declare and initialize a new map in the same line with this syntax.
	n := map[string]int{"foo": 1, "bar": 2}
	fmt.Println("map:", n)

	keys := []string{}
	for k := range n {
		keys = append(keys, k)
	}
	fmt.Println("map keys:", keys)
}
