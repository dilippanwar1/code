// The json package provides Decoder and Encoder types to support the
// common operation of reading and writing streams of JSON data.

package main

import (
	"encoding/json"
	"log"
	"os"
)

func main() {
	// Decoder reads the JSON-encoded value from its input and stores
	// it in the value pointed to by v.
	dec := json.NewDecoder(os.Stdin)
	// Encoder writes the JSON encoding of v to the stream, followed
	// by a newline character.
	enc := json.NewEncoder(os.Stdout)

	for {
		var v map[string]interface{}
		// Input something like: {"Name": "deyuan"}.
		if err := dec.Decode(&v); err != nil {
			log.Println(err)
			return
		}
		for k := range v {
			if k != "Name" {
				delete(v, k)
			}
		}
		if err := enc.Encode(&v); err != nil {
			log.Println(err)
		}
	}
}
