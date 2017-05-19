package main

import (
	"fmt"
)

func main() {
	data := map[string]string{"abc": "123"}

	for key, val := range data {
		if key == "abc" {
			delete(data, "abc")
			data[key] = "321"
			fmt.Printf("processing %v:%v\n", key, val)
		}
	}

	fmt.Println(data)
}
