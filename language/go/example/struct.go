package main

import "fmt"


type Person struct {
	name string
	age int
}


func main() {

	// This will create a new struct.
	fmt.Println(Person{"Deyuan", 25})

	// Use named fields.
	fmt.Println(Person{name: "Deyuan", age: 25})

	// Omitted fields will be zero-valued.
	fmt.Println(Person{name: "Deyuan"})

	// Create a pointer.
	fmt.Println(&Person{"Deyuan", 25})

	// Dot notation for both variable and pointer.
	s := Person{name: "Deyuan", age: 25}
	fmt.Println(s.name)

	sp := &s
	fmt.Println(sp.name)

	// Create a Person with all default value.
	p := Person{}
	fmt.Println(p)

	// Create a slice of Person with default value.
	people := []Person{}
	people = append(people, Person{"Deyuan", 26})
	people = append(people, Person{"Sijia", 26})
	fmt.Println(people)
}
