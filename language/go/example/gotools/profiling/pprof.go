// Run the program with:
//   $ go run pprof.go
// Then use 'go tool' to do profiling, e.g.
//   $ go tool pprof http://localhost:9999/debug/pprof
//
// Reading:
//   https://blog.golang.org/profiling-go-programs
package main

import (
	"fmt"
	"net/http"
	_ "net/http/pprof"
)

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello world from my Go program!\n")
}

func main() {
	// 'http.HandleFunc' uses a default ServeMux; ServeMux is an HTTP request multiplexer.
	http.HandleFunc("/hello", helloHandler)
	http.ListenAndServe("localhost:9999", nil)
	select {}
}
