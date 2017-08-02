package main

import "fmt"

func zeroval(ival int) {
	ival = 0
}

func zeroptr(iptr *int) {
	*iptr = 0
}

func main() {
	i := 1
	fmt.Println("Initial:", i) // 1

	zeroval(i)
	fmt.Println("zeroval():", i) // 1

	zeroptr(&i)
	fmt.Println("zeroptr():", i) // 0

	fmt.Println("Pointer:", &i)     // Print i's address
	fmt.Printf("Pointer: %p\n", &i) // Print i's address
}
