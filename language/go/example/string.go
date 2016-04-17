package main

import (
	"fmt"
	"strings"
	"unicode"

	"github.com/blang/semver"
)

func main() {
	// Multiline()
	// EmptyString()
	// UpperLower()
	// Slicing()
	// ParseString()
	TrimPrefix()
}

func TrimPrefix() {
	fmt.Println(strings.TrimPrefix("/proxy/api/v1/create", "abce/"))
	fmt.Println(strings.TrimPrefix("/proxy/api/v1/create", "/proxy"))
}

func Multiline() {
	s :=
		`String using back quote
for multi line.`

	fmt.Println(s)
}

func RuneUnicode() {
	// Unicode
	s := "邓"
	fmt.Println(len(s)) // 3

	_ = '邓' // This is a rune
}

func EmptyString() {
	// Empty string do not occpy any space.
	s := ""
	fmt.Printf("This is |%s|\n", s)
}

func UpperLower() {
	s := strings.ToUpper("i-e7mppdl7")
	a := []rune(s)
	a[0] = unicode.ToLower(a[0])
	fmt.Println(string(a))
}

func Slicing() {
	s := "trysubstring"
	fmt.Println(getShortHash(s, 8))
}

func getShortHash(userId string, length int) string {
	if len(userId) < length {
		return userId
	}
	return userId[len(userId)-length:]
}

func ParseString() {
	fmt.Println(parse("v1.2.3-2016-12"))
}

func parse(gitversion string) (semver.Version, error) {
	var seen bool
	gitversion = strings.TrimLeftFunc(gitversion, func(ch rune) bool {
		if seen {
			return false
		}
		if ch == 'v' {
			seen = true
			return true
		}
		return unicode.IsSpace(ch)
	})

	return semver.Make(gitversion)
}
