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

func main() {
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
}
