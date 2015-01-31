package main

import (
	"encoding/json"
	"fmt"
	"reflect"
	"time"
)

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

	if err := json.Unmarshal([]byte(input), &val); err != nil {
		panic(err)
	}

	fmt.Println(val)
	for k, v := range val {
		fmt.Println(k, reflect.TypeOf(v))
	}
}

func main() {
	custom()
}
