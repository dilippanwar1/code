package main

import (
	"fmt"
	"net/http"
	"time"
)

func flushHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Inside flushHandler")
	fmt.Fprintf(w, "Hello world from my Go program!\n")

	// Create a http.Flusher to allow server to send buffered data.
	flusher, _ := w.(http.Flusher)
	flusher.Flush()

	for i := 0; i < 5; i++ {
		time.Sleep(time.Second)
		fmt.Println("Flushing result")
		fmt.Fprintf(w, "Hello world from my Go program!\n")
		flusher.Flush()
	}
}

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Inside helloHandler")
	fmt.Fprintf(w, "Hello world from my Go program!\n")
}

func main() {
	// 'http.HandleFunc' uses a default ServeMux; ServeMux is an HTTP request multiplexer.
	http.HandleFunc("/hello", helloHandler)
	http.HandleFunc("/flush", flushHandler)

	// Listen for connections at port 9999 on the local machine.
	http.ListenAndServe("localhost:9999", nil)
}
