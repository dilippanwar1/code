package main

import (
	"fmt"
	"reflect"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	person := Person{
		Name: "Deyuan",
		Age:  25,
	}

	// This assignment will make a new copy.
	copied := person
	copied.Name = "Baby"

	fmt.Println(person)
	fmt.Println(copied)
	fmt.Printf("%p\n", &person) // 'person' and 'copied' have different address
	fmt.Printf("%p\n", &copied)
	fmt.Println(reflect.DeepEqual(person, copied)) // false

	var person2 Person
	// Cannot assign nil to person2, the following assignment is wrong:
	//   person2 = nil
	fmt.Println(person2)

	var person3 *Person
	person3 = nil // This is valid.
	fmt.Println(person3)
}
