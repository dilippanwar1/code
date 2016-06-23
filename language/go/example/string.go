package main

import (
	"fmt"
	"reflect"
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
	// TrimPrefix()
	RuneUnicode()
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
	// Unicode (string)
	s := "邓"
	fmt.Println(len(s))            // 3
	fmt.Println(reflect.TypeOf(s)) // string

	// This is a rune.
	r := '邓'
	fmt.Println(reflect.TypeOf(r)) // int32
	// You can't get length of rune.
	//  fmt.Println(len(r))

	// A bit of rune facts.
	rr := "邓德源"
	fmt.Println(len(rr))               // 9
	fmt.Println(reflect.TypeOf(rr[0])) // uint8
	fmt.Println(rr[0])                 // 233
	fmt.Println(rr)                    // 邓德源

	// To index rune, we'll need to convert to []rune.
	fmt.Println(string([]rune("Hello, 世界")[8])) // UTF-8
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
