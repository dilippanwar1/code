package main

import (
	"bytes"
	"encoding/json"
	"fmt"
)

func main() {
	var data = []byte(`{"status": 200}`)

	var result map[string]interface{}
	// By default, json decode will decode '200' into float64. UseNumber causes the
	// Decoder to unmarshal a number into an interface{} as a Number instead of as
	// a float64.
	var decoder = json.NewDecoder(bytes.NewReader(data))
	decoder.UseNumber()

	if err := decoder.Decode(&result); err != nil {
		fmt.Println("error:", err)
		return
	}

	var status, _ = result["status"].(json.Number).Int64() //ok
	fmt.Println("status value:", status)
}
