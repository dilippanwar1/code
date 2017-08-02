package main

import "fmt"

func getVal() (int, error) {
	return 1, nil
}

func getValError() (int, error) {
	return 2, fmt.Errorf("error")
}

func main() {
	outer := "Foo"
	if true {
		inner := "Bar"
		fmt.Println(inner)
	}
	fmt.Println(outer)

	// Compile error: inner is undefined.
	//   fmt.Println(inner)

	// Output:
	// One: 1
	// Ah oh oh 2
	// Two: 2
	var val int
	var err error
	if val, err = getVal(); err != nil {
		fmt.Println("Ah oh", val)
	}
	fmt.Println("One:", val)

	if val, err = getValError(); err != nil {
		fmt.Println("Ah oh oh", val)
	}
	fmt.Println("Two:", val)
}
