package main

import "fmt"

func zeroval(ival int) {
	ival = 0
}

func zeroptr(iptr *int) {
	*iptr = 0
}

type Person struct {
	name string
}

func main() {
	i := 1
	fmt.Println("Initial:", i) // 1

	zeroval(i)
	fmt.Println("zeroval():", i) // 1

	zeroptr(&i)
	fmt.Println("zeroptr():", i) // 0

	fmt.Println("Pointer:", &i) // Print i's address

	person := &Person{name: "deyuan"}
	fmt.Printf("%p\n", person)
	personX := *person
	fmt.Printf("%p\n", &personX) // personX has different address than person
	fmt.Println(person)
	fmt.Println(personX) // personX has some content as person
}
