package main

import (
	"fmt"
	"reflect"
)

type TaggedStruct struct {
	F string `species:"gopher" color:"blue"`
	I string `age:"100"`
}


func main() {
	s := TaggedStruct{}						// create an empty Struct
	st := reflect.TypeOf(s)				// st => main.TaggedStruct

	field0 := st.Field(0)
	fmt.Println(field0.Tag.Get("color"), field0.Tag.Get("species"))

	field1 := st.Field(1)
	// The second Get will return empty.
	fmt.Println(field1.Tag.Get("age"), field1.Tag.Get("species"))
}
