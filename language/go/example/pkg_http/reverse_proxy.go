package main

import (
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func main() {
	// Get a URL object from url link.
	u, err := url.Parse("http://www.cnn.com")
	if err != nil {
		log.Fatal(err)
	}

	// Create a proxy server.
	reverse_proxy := httputil.NewSingleHostReverseProxy(u)
	http.Handle("/", reverse_proxy)

	// The proxy server listens to 8888.  When client connects to this port,
	// the reverser proxy will pass request to "http://www.cnn.com".
	if err = http.ListenAndServe(":8888", nil); err != nil {
		log.Fatal(err)
	}
	log.Println("Server started")
}
