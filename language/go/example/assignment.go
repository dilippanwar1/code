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
	fmt.Printf("%p\n", &person)
	fmt.Printf("%p\n", &copied)
	fmt.Println(reflect.DeepEqual(person, copied))
}
