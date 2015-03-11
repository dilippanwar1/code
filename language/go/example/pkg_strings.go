package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	fmt.Println(len(strings.Fields("foo1                <none>              Ready")))
	fmt.Println(strings.Fields("foo1                <none>\n              Ready"))

	fmt.Println(strings.Join([]string{"a", "b"}, ","))

	i := 10021312
	fmt.Println(string(i))       // This will convert to ascii
	fmt.Println(strconv.Itoa(i)) // This will return "100"
}
