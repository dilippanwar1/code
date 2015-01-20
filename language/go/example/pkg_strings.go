package main

import (
	"fmt"
	"strings"
)

func main() {
	fmt.Println(len(strings.Fields("foo1                <none>              Ready")))
	fmt.Println(strings.Fields("foo1                <none>\n              Ready"))
}
