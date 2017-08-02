package main

import (
	"fmt"
	"reflect"
)

type MyType struct {
	A int
	B string
}

func main() {
	x := MyType{}
	Fuzz(&x)
	fmt.Println(x)
}

// Fuzz will fill input struct 'v' with random value.
func Fuzz(v interface{}) {
	// Must be a pointer; otherwise we won't be able to set the values.
	if reflect.TypeOf(v).Kind() != reflect.Ptr {
		panic("must pass a pointer to Fuzz")
	}
	// Settability is true only when we derefernce the pointer, i.e. call
	// doFuzz with `reflect.ValueOf(v)` will do nothing.
	doFuzz(reflect.ValueOf(v).Elem())
}

func doFuzz(v reflect.Value) {
	if !v.CanSet() {
		panic("cannot set field")
		return
	}

	switch v.Kind() {
	case reflect.Struct:
		for i := 0; i < v.NumField(); i++ {
			doFuzz(v.Field(i))
		}
	case reflect.Int:
		v.SetInt(1)
	case reflect.String:
		v.SetString("hello")
	default:
		fmt.Println("Unknown kind", v.Kind())
	}
}
