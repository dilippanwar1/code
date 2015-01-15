package main

import "fmt"

type Data struct {
	Name string
	Desc string
}

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

	// Note range will do a copy of slice value.
	var list1 = []Data{{"Item11", "desc of 11"}, {"Item12", "desc of 12"}, {"Item13", "desc of 13"}}
	var list2 = []*Data{{"Item21", "desc of 1"}, {"Item22", "desc of 2"}, {"Item23", "desc of 23"}}

	// 1. This will not work, as range yields a copy not pointer.
	for _, item := range list1 {
		item.Desc = "change the desc"
	}
	fmt.Println(list1)

	// 2. This works as the copy is anyway pointer to element.
	for _, item := range list2 {
		item.Desc = "change the desc"
	}
	for _, it := range list2 {
		fmt.Print(*it, " ")
	}

	// 3. Only way on list is without range :(
	for i := 0; i < len(list1); i++ {
		list1[i].Desc = "change the desc"
	}
	fmt.Println("\n", list1)
}
