package main

import (
	"fmt"
	"reflect"
)

func main() {
	slice1 := []string{"1", "2"}
	slice2 := []string{"2", "1"}

	fmt.Println(reflect.DeepEqual(slice1, slice2))
}
