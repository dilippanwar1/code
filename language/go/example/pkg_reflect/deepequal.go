package main

import (
	"fmt"
	"reflect"
)

func main() {
	slice1 := []string{"1", "2"}
	slice2 := []string{"2", "1"}
	fmt.Println(reflect.DeepEqual(slice1, slice2)) // False

	slice3 := []string{}
	slice4 := []string{}
	fmt.Println(reflect.DeepEqual(slice3, slice4)) // True

	slice5 := []string{}
	var slice6 []string
	fmt.Println(reflect.DeepEqual(slice5, slice6)) // False

	map1 := map[string]string{"ddy": "Deyuan Deng", "lsj": "Sijia Luo"}
	map2 := map[string]string{"lsj": "Sijia Luo", "ddy": "Deyuan Deng"}
	fmt.Println(reflect.DeepEqual(map1, map2))   // True
	fmt.Println(reflect.DeepEqual(&map1, &map2)) // True
}
