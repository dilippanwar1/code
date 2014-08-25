// This file demonstrates a typical usage of reflect.
//
// Package reflect implements run-time reflection, allowing a program to
// manipulate objects with arbitrary types. The typical use is to take a
// value with static type interface{} and extract its dynamic type information
// by calling TypeOf, which returns a Type.
//
// A call to ValueOf returns a Value representing the run-time data. Zero
// takes a Type and returns a Value representing a zero value for that type.
//

package main

import (
	"fmt"
	"reflect"
)

type Car struct {
	made string
	year int
}

type Bike struct {
	made  string
	brand string
}

type Train struct {
	speed int
	size  int
}

func main() {

	// 'vehicle' is a map from vehicle type name to its corresponding struct.
	// Using interface{} can help store them in the same map.
	vehicle := map[string]interface{}{
		"car":   Car{"Ford", 2008},
		"bike":  Bike{"Fiet", "CC"},
		"train": Train{200, 100},
	}

	// 'typeMap' is a map from vehicle type name to its corresponding type.
	// All values in map 'vehicle' have static type interface{}, the 'typMap'
	// holds their dynamic tpyes.
	typeMap := make(map[string]reflect.Type)
	for name, obj := range vehicle {
		typeMap[name] = reflect.TypeOf(obj)
	}

	fmt.Println(vehicle)
	fmt.Println(typeMap)

	// ValueOf returns a new Value initialized to the concrete value
	// stored in the interface.
	var mystery interface{} = Car{"BMW", 2014}
	fmt.Println(reflect.TypeOf(mystery))

	// 'mystery_value' has type: "reflect.Value".
	mystery_value := reflect.ValueOf(mystery)
	fmt.Println(mystery_value.Kind())    // struct
	fmt.Println(mystery_value.IsValid()) // true
	fmt.Println(mystery_value.FieldByName("made"))
}
