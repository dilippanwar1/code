package main

import "fmt"

func main() {

	nums := []int{2, 3, 4}
	sum := 0

	// range provides both the index and value for each entry.
	for _, num := range nums {
		sum += num
	}
	fmt.Println("sum:", sum)

	// range provides index if there is only one variable at left.
	for i := range nums {
		fmt.Println("i:", i)
	}

	for i, num := range nums {
		if num == 3 {
			fmt.Println("index of value 3:", i)
		}
	}

	// range provides key/value for map.
	kvs := map[string]string{"a": "apple", "b": "banana"}
	for k, v := range kvs {
		fmt.Printf("%s -> %s\n", k, v)
	}

	// range on string literal: index of byte and byte code.
	for i, c := range "go" {
		fmt.Println(i, c)
	}
}
