// Run the example with:
//   $ go run -race example.go
// will print information about an potential race. A data race occurs when two
// goroutines access the same variable concurrently and at least one of the
// accesses is a write.
//
// Alternatively, use:
//   $ go build -race example.go
//   $ ./example

package main

import "fmt"

func main() {
	c := make(chan bool)
	m := make(map[string]string)
	go func() {
		m["1"] = "a" // First conflicting access.
		c <- true
	}()
	m["2"] = "b" // Second conflicting access.
	<-c
	for k, v := range m {
		fmt.Println(k, v)
	}
}
