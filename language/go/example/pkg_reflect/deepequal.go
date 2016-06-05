package main

import (
	"fmt"
	"reflect"
)

type Data struct {
	A string
	B string
}

func main() {
	slice1 := []string{"1", "2"}
	slice2 := []string{"2", "1"}
	fmt.Println(reflect.DeepEqual(slice1, slice2)) // false

	slice3 := []string{}
	slice4 := []string{}
	fmt.Println(reflect.DeepEqual(slice3, slice4)) // true

	slice5 := []string{}
	var slice6 []string
	fmt.Println(reflect.DeepEqual(slice5, slice6)) // false

	map1 := map[string]string{"ddy": "Deyuan Deng", "lsj": "Sijia Luo"}
	map2 := map[string]string{"lsj": "Sijia Luo", "ddy": "Deyuan Deng"}
	fmt.Println(reflect.DeepEqual(map1, map2))   // true
	fmt.Println(reflect.DeepEqual(&map1, &map2)) // true

	struct1 := Data{A: "A", B: "B"}
	struct2 := Data{}
	fmt.Println(reflect.DeepEqual(struct1, struct2)) // false
}
