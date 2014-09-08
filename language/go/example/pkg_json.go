package main

import (
	"bytes"
	"encoding/json"
	"fmt"
)

type Message struct {
	Name string
	Body string
	Time int64
}

func basics() {
	// Create an instance of Message struct.
	m := Message{"Alice", "Hello", 1234567890}

	// We can marshal a JSON-encoded version of m using json.Marshal. Marshal
	// here means take a Go object, convert it to json, where json is represented
	// as bytes.
	b, _ := json.Marshal(m)

	if bytes.Equal(b, []byte(`{"Name":"Alice","Body":"Hello","Time":1234567890}`)) {
		// Every byte is ASCII of the corresponding char in the json string. Note
		// the number printed by Go is in decimal:
		// [123 34 78 97 109 101 34 58 34 65 108 105 99 101 34 44 34 66 111 100 121
		//  34 58 34 72 101 108 108 111 34 44 34 84 105 109 101 34 58 49 50 51 52 53
		//  54 55 56 57 48 125]
		fmt.Println("Bytes equal:", b)
	}
	// Print json string.
	fmt.Println(string(b))

	// If b contains valid JSON that fits in Message, after the call err will be
	// nil and the data from b will have been stored in the struct mm.
	var mm Message
	json.Unmarshal(b, &mm)
	fmt.Println(mm)

	// Only known field (Name) will be populated.
	var mmm Message
	b = []byte(`{"Name":"Bob","Food":"Pickle"}`)
	json.Unmarshal(b, &mmm)
	fmt.Println(mmm)
}

type FamilyMember struct {
	Name    string
	Age     int
	Parents []string
}

// The json package uses map[string]interface{} and []interface{} values to
// store arbitrary JSON objects and arrays; it will happily unmarshal any valid
// JSON blob into a plain interface{} value. The default concrete Go types are:
//   bool for JSON booleans,
//   float64 for JSON numbers,
//   string for JSON strings, and
//   nil for JSON null.
func generic() {
	// A wire format JSON data.
	b := []byte(`{"Name":"Wednesday", "Age":6, "Parents":["Gomez","Morticia"]}`)

	var f interface{}
	json.Unmarshal(b, &f)

	// Now f is a 'map' containing the JSON. Note it's type is still interface{}.
	// f = map[string]interface{}{
	//   "Name": "Wednesday",
	//   "Age":  6,
	//   "Parents": []interface{}{
	// 		"Gomez",
	// 		"Morticia",
	//   },
	// }
	fmt.Println(f)

	m := f.(map[string]interface{})
	for k, v := range m {
		switch vv := v.(type) {
		case string:
			fmt.Println(k, "is string", vv)
		case int:
			fmt.Println(k, "is int", vv)
		case float32:
			fmt.Println(k, "is float32", vv)
		case float64:
			fmt.Println(k, "is float64", vv)
		case []interface{}:
			fmt.Println(k, "is an array:")
			for i, u := range vv {
				fmt.Println(i, u)
			}
		default:
			fmt.Println(k, "is of a type I don't know how to handle")
		}
	}

	// To populate the Parents field, Unmarshal allocated a new slice behind
	// the scenes. This is typical of how Unmarshal works with the supported
	// reference types (pointers, slices, and maps).
	var fm FamilyMember
	json.Unmarshal(b, &fm)
	fmt.Println(fm)
}

func main() {
	basics()
	generic()
}
