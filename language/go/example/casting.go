package main

import (
	"fmt"
	"reflect"
)

type Animal interface {
	Speak() string
}

type Dog struct {
}

func (c Dog) Speak() string {
	return "Woof!"
}

func (c Dog) Eat() string {
	return "Rib!"
}

type Animals []Animal

func main() {
	dog := Dog{}
	fmt.Println(dog.Eat())
	fmt.Println(dog.Speak())

	// Cannot call Eat on animalType, although reflect show animalType
	// is of type main.Dog.
	animalType := Animal(dog)
	// fmt.Println(animalType.Eat())
	fmt.Println(animalType.Speak())
	fmt.Println(reflect.TypeOf(animalType))

	var animals []Animal
	test := Animals(animals)
	fmt.Println(test)
	fmt.Println(reflect.TypeOf(test))    // Type: main.Animals
	fmt.Println(reflect.TypeOf(animals)) // Type: []main.Animal
}
