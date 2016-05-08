package main

import (
	"fmt"
	"path"
)

func main() {
	name := "/tmp"
	fmt.Println(path.Dir(name))
	fmt.Println(path.Base(name))

	name = "/"
	fmt.Println(path.Dir(name))  // output: "/"
	fmt.Println(path.Base(name)) // output: "/"

	name = "/etc/"
	fmt.Println(path.Clean(name)) // output: "/"
}
