package main

import (
	"encoding/json"
	"fmt"
	"reflect"
	"time"
)

// The input string value 'Thu May 31 00:00:01 +0000 2012' is not a valid
// time.Time type. To marshal/unmarshal, we need to define out custom type.
var input = `
{
  "created_at": "Thu May 31 00:00:01 +0000 2012"
}
`

func naive() {
	var val map[string]time.Time

	// We expect error here, since the 'input' is RubyDate, which cannot be
	// parsed into time.Time.
	if err := json.Unmarshal([]byte(input), &val); err != nil {
		panic(err)
	}

	fmt.Println(val)
	for k, v := range val {
		fmt.Println(k, reflect.TypeOf(v))
	}
}

// The encoding/json package looks to see if values passed to json.Unmarshal
// satisfy the json.Unmarshaler interface, which looks like this:
//   type Unmarshaler interface {
//     UnmarshalJSON([]byte) error
//   }
type Timestamp time.Time

func (t *Timestamp) UnmarshalJSON(b []byte) error {
	v, err := time.Parse(time.RubyDate, string(b[1:len(b)-1]))
	if err != nil {
		return err
	}
	*t = Timestamp(v)
	return nil
}

func custom() {
	var val map[string]Timestamp

	// Convert json to a Go object.
	if err := json.Unmarshal([]byte(input), &val); err != nil {
		panic(err)
	}

	fmt.Println(val) // output: map[created_at:{63474019201 0 0xc208064060}]
	for k, v := range val {
		fmt.Println(k, reflect.TypeOf(v))
	}
}

func main() {
	// naive()
	custom()
}
