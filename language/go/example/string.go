package main

import "fmt"

func main() {

	s :=
		`String using back quote
for multi line.`

	fmt.Println(s)

	s = ""
	fmt.Printf("This is |%s|\n", s)
}
