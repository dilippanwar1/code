package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"os"
)

func main() {
	// basicDecode()
	fileDecode()
}

func basicDecode() {
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

func fileDecode() {
	file, err := os.Open("./data.json")
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}
	enc := json.NewDecoder(file)

	for err == nil {
		var data map[string]string
		err = enc.Decode(&data)
		if err != nil {
			break
		}
		fmt.Println(data)
	}
}
