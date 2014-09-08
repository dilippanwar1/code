package main

import "fmt"

type Animal interface {
	Speak() string
}

type Dog struct {
}

func (d Dog) Speak() string {
	return "Woof!"
}

type Cat struct {
}

func (c *Cat) Speak() string {
	return "Meow!"
}

func main() {
	// Note here only *Cat implements the Animal interface, so we need to pass
	// &Cat{} instead of Cat{}. However, we can either pass Dog{} or &Dog{} even
	// though only Dog implements the Animal interface. This works because a
	// pointer type can access the methods of its associated value type, but not
	// vice versa. That is, a *Dog value can utilize the Speak method defined on
	// Dog, but as we saw earlier, a Cat value cannot access the Speak method
	// defined on *Cat. The reason behinds all this is that in Go, everything is
	// passed by value. So when a method is defined as *Cat, and we pass a Cat,
	// there is no way for the method to know the original Cat (since the Cat value
	// received is copied); however, we can always get the value from pointers,
	// like the case with passing *Dog.
	animals := []Animal{Dog{}, &Dog{}, &Cat{}}
	for _, animal := range animals {
		fmt.Println(animal.Speak())
	}
}
