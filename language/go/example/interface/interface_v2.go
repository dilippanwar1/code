package main

import "fmt"

func main() {
	var data *byte
	var in interface{}

	fmt.Println(data, data == nil) // Prints: <nil> true
	fmt.Println(in, in == nil)     // Prints: <nil> true

	// The interface type and value fields are populated based on the type and value
	// of the variable used to create the corresponding interface variable.
	// Interface variables will be "nil" ONLY when their type and value fields are nil.
	// Therefore, the result here is that 'data' is nil, but 'in' is not nil, since 'in'
	// has non-nil type.
	in = data
	fmt.Println(in, in == nil) // Prints: <nil> false
}
