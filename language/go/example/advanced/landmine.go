package main

import "fmt"

// Loop variables are scoped outside the loop.
func print(pi *int) { fmt.Println(*pi) }
func lookScope() {
	for i := 0; i < 10; i++ {
		defer fmt.Println(i)                    // OK; prints 9 ... 0
		defer func() { fmt.Println(i) }()       // WRONG; prints "10" 10 times
		defer func(i int) { fmt.Println(i) }(i) // OK
		defer print(&i)                         // WRONG; prints "10" 10 times
		go fmt.Println(i)                       // OK; prints 0 ... 9 in unpredictable order
		go func() { fmt.Println(i) }()          // WRONG; totally unpredictable.
	}

	// Same for key & value as i!
	// for key, value := range myMap {
	// }
}

// Nil interface is not the same as having a nil pointer in the interface.
type Cat interface {
	Meow()
}

type Tabby struct{}

func (*Tabby) Meow() { fmt.Println("meow") }

func GetACat() Cat {
	var myTabby *Tabby = nil
	// Oops, we forgot to set myTabby to a real value
	return myTabby
}

func GetAnotherCat() Cat {
	return nil
}

func TestGetACat() {
	// This will NOT be detected
	if GetACat() == nil {
		fmt.Println("Forgot to return a real cat!")
	}

	// This will be detected
	if GetAnotherCat() == nil {
		fmt.Println("Forgot to return another real cat!")
	}
}

func main() {
	TestGetACat()
}
