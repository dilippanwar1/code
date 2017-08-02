package main

import (
	"fmt"
	"reflect"
)

type Pet struct {
	Name string
}

type Person struct {
	Name string
	Age  int
	Pet  []Pet
}

func main() {
	person := Person{
		Name: "Deyuan",
		Age:  25,
		Pet: []Pet{
			Pet{"dudu"},
			Pet{"huahua"},
		},
	}

	// This assignment will make a new copy of 'person', but note
	// that the Pet field will share the same underline store.
	copied := person
	fmt.Println(reflect.DeepEqual(person, copied)) // true

	person.Pet[0].Name = "dudu2"
	// Both 'person' and 'copied' will print 'dudu2'.
	fmt.Println(person)
	fmt.Println(copied)
	// The two addresses are the same.
	fmt.Printf("%p\n", person.Pet)
	fmt.Printf("%p\n", copied.Pet)
	// The two addresses are different (store pointer value).
	fmt.Printf("%p\n", &person.Pet)
	fmt.Printf("%p\n", &copied.Pet)
}
