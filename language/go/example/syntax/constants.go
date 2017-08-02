package main

import "fmt"

// Define single constant.
const thing = 5      // untyped
const thing2 int = 5 // typed - only used in int expressions

// Enums come by putting a bunch of consts in parens.
const (
	One_1   = 1
	Two_1   = 2
	Three_1 = 4
)

// You can use iota to create these values. Within a const group, it
// starts at 0, and then increments for each expression.
const (
	One_2   = 1 << iota // 1 (i.e. 1 << 0)
	Two_2               // 2 (i.e. 1 << 1)
	Three_2             // 4 (i.e. 1 << 2)
)

const (
	SET    int = iota // 0
	ADD               // 1
	REMOVE            // 2
	UPDATE            // 3
)

const (
	a = iota // a == 0
	b = 5    // b == 5
	c = iota // c == 2, iota is incremented every at each line.
)

// Giving custom types methods is the OOP of golang.
type Type int

const (
	One_3   Type = 1 << iota // 1 (iota is independent in constant ()
	Two_3                    // 2 (i.e. 1 << 1)
	Three_3                  // 4 (i.e. 1 << 2)
)

func (t Type) String() string {
	s := ""
	if t&One_3 == One_3 {
		s += "One"
	} else if t&Two_3 == Two_3 {
		s += "Two"
	} else if t&Three_3 == Three_3 {
		s += "Three"
	}
	return s
}

func main() {
	fmt.Println(One_2)
	fmt.Println(SET)
	fmt.Println(c)
	val := One_3
	fmt.Println(val.String())
}
