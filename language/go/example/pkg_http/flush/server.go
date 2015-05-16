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
	flusher, ok := w.(http.Flusher)
	if !ok {
		fmt.Println("Can't convert ResponseWriter to Flusher")
	}
	flusher.Flush()

	for i := 0; i < 5; i++ {
		time.Sleep(time.Second)
		fmt.Println("Flushing result")
		fmt.Fprintf(w, "Hello world from my Go program!\n")
		flusher.Flush()
	}
}

func main() {
	http.HandleFunc("/flush", flushHandler)
	http.ListenAndServe("localhost:9999", nil)
}
