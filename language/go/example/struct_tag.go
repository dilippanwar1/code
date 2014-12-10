package main

import (
	"encoding/json"
	"fmt"
	"reflect"
)

type TaggedStruct struct {
	F string `json:"f" species:"gopher"`
	I string `json:"i,omitempty" age:"100"`
	N string `json:"-"`
}

func main() {
	s := TaggedStruct{}     // create an empty Struct
	st := reflect.TypeOf(s) // st => main.TaggedStruct

	// To get tag value, we need reflect package.
	field0 := st.Field(0)
	fmt.Println(field0.Tag.Get("json"), field0.Tag.Get("species"))

	field1 := st.Field(1)
	fmt.Println(field1.Tag.Get("json"), field1.Tag.Get("species"))

	field2 := st.Field(2)
	fmt.Println(field2.Tag.Get("json"))

	// Struct values encode as JSON objects. Each exported struct field
	// becomes a member of the object unless:
	// - the field's tag is "-", or
	// - the field is empty and its tag specifies the "omitempty" option.
	j, err := json.Marshal(s)
	if err != nil {
		fmt.Println("Can't convert to json")
	}
	fmt.Println(string(j))
}
