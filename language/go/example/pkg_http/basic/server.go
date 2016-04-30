package main

import (
	"fmt"
	"net/http"
	"time"
)

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Inside hello handler")
	fmt.Fprintln(w, "Client Headers")
	for k, v := range r.Header {
		fmt.Fprintf(w, "  %v=%v\n", k, v)
	}
	fmt.Fprintf(w, "Hello world from my Go program!\n")
}

func main() {
	// 'http.HandleFunc' uses a default ServeMux; ServeMux is an HTTP request multiplexer.
	http.HandleFunc("/hello", helloHandler)

	// Listen for connections at port 9999 on the local machine. Handler is typically nil,
	// in which case the DefaultServeMux is used.
	go http.ListenAndServe(":9999", nil)

	// Create our own server.
	s := &http.Server{
		Addr: ":9998",
		// 'http.HandlerFunc' is a type which converts ordinary functions to http handlers,
		// i.e we convert helloHandler to a HandlerFunc which implements ServeHTTP based on
		// helloHandler.
		Handler:        http.HandlerFunc(helloHandler),
		ReadTimeout:    10 * time.Second,
		WriteTimeout:   10 * time.Second,
		MaxHeaderBytes: 1 << 20,
	}
	go s.ListenAndServe()

	fmt.Println("Listening on :9998/ and 9999/hello")

	select {}
}
