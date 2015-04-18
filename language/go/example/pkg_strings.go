package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	// Fields splits the string s around each instance of
	// one or more consecutive white space characters.
	fmt.Println(len(strings.Fields("foo1                <none>              Ready"))) // 3
	fmt.Println(strings.Fields("foo1                <none>\n              Ready"))    // [foo1 <none> Ready]

	fmt.Println(strings.Join([]string{"a", "b"}, ",")) // a,b

	i := 100
	fmt.Println(string(i))       // This will convert to ascii 'd'
	fmt.Println(strconv.Itoa(i)) // This will return "100"
}
