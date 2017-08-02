// Experiment with golang reflection.
//
// Note reflect.Type is an interface while reflect.Value is a struct implementing
// a lot of methods (not satisfying reflect.Type interface). You can get value's
// type via reflect.Value.Type().
//
// A variable holds value of a type. Go value is stored in-memory and accessed via
// variable or reflect.Value. reflect.Value contains more information about the
// value. reflect.Type contains type informaation.
//
// https://blog.golang.org/laws-of-reflection

package main

import (
	"fmt"
	"reflect"
	"time"
)

func main() {
	RuntimeType()
	fmt.Println()
	FunctionReflect()
	fmt.Println()
	PointerReflect()
}

// Every variable in Go has a static type, even for variable of type interface{}.
// reflect.TypeOf returns the 'run-time' Type of a variable; that is, for normal
// type, TypeOf returns its type directly, for interface variable, TypeOf returns
// the underline type it holds.
func RuntimeType() {
	a := &time.Time{}
	b := time.Time{}
	fmt.Println("Type of a:", reflect.TypeOf(a)) // *time.Time
	fmt.Println("Type of b:", reflect.TypeOf(b)) // time.Time

	var c interface{}
	c = a
	fmt.Println("Type of c when assigned to a:", reflect.TypeOf(c)) // *time.Time
	c = b
	fmt.Println("Type of c when assigned to b:", reflect.TypeOf(c)) // time.Time

	fmt.Println("Kind of a:", reflect.ValueOf(a).Kind()) // ptr
	fmt.Println("Kind of a:", reflect.TypeOf(a).Kind())  // ptr
}

func AFunc(t *time.Time) error {
	fmt.Println(t)
	return nil
}

// A bit of reflection on function.
func FunctionReflect() {
	funcType := reflect.TypeOf(AFunc)
	fmt.Println(funcType)        // func(*time.Time) error
	fmt.Println(funcType.In(0))  // *time.Time
	fmt.Println(funcType.Kind()) // func
	// There are quite a few methods on reflect.Type, but not all of them
	// can be called, e.g. reflect.Type.Key() can only be called on Map type;
	// reflect.Type.FieldByName can only be called on struct type, etc.
	// fmt.Println(funcType.Key())
	// fmt.Println(funcType.FieldByName("Hello"))

	funcValue := reflect.ValueOf(AFunc)
	fmt.Println(funcValue) // 0x2bb0
	// reflect.Value.Type() will return reflect.Type, similar to reflect.TypeOf
	fmt.Println(funcValue.Type()) // func(*time.Time) error
	fmt.Println(funcValue.Kind()) // func
}

type MyType struct {
	A int
	B string
}

// A bit of reflection on pointer.
func PointerReflect() {
	x := MyType{}
	fmt.Println(reflect.TypeOf(x), reflect.ValueOf(x))
	fmt.Println(reflect.TypeOf(&x), reflect.ValueOf(&x), reflect.ValueOf(&x).Elem())

	// Addr returns a pointer value representing the address of v. For pointer,
	// it must be the result of dereferencing a pointer.
	fmt.Println(reflect.ValueOf(x).CanAddr())         // false
	fmt.Println(reflect.ValueOf(&x).CanAddr())        // false
	fmt.Println(reflect.ValueOf(&x).Elem().CanAddr()) // true

	fmt.Println(reflect.ValueOf(x).CanSet())         // false
	fmt.Println(reflect.ValueOf(&x).CanSet())        // false
	fmt.Println(reflect.ValueOf(&x).Elem().CanSet()) // true
}
