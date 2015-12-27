package main

import (
	"fmt"
	"strings"
	"unicode"
)

func main() {

	s :=
		`String using back quote
for multi line.`

	fmt.Println(s)

	// Empty string do not occpy any space.
	s = ""
	fmt.Printf("This is |%s|\n", s)

	s = strings.ToUpper("i-e7mppdl7")
	a := []rune(s)
	a[0] = unicode.ToLower(a[0])
	fmt.Println(string(a))

	ss := "trysubstring"
	fmt.Println(getShortHash(ss, 8))
}

func getShortHash(userId string, length int) string {
	if len(userId) < length {
		return userId
	}
	return userId[len(userId)-length:]
}
