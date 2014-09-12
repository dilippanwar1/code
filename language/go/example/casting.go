package main

import (
	"fmt"
	"reflect"
)

type Dog struct {
}

type Animal interface {
	Speak() string
}

func (c Dog) Speak() string {
	return "Woof!"
}

func (c Dog) Eat() string {
	return "Rib!"
}

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
}
