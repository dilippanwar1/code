package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)


// Use Get method in http package directy, it is a wrapper around
// DefaultClient.Get().
func UseGet() {
	res, err := http.Get("http://www.google.com/robots.txt")
	if err != nil {
		log.Fatal(err)
	}

	robots, err := ioutil.ReadAll(res.Body)
	// Client must close body when finish with it.
	res.Body.Close()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(robots)
}


// For control over HTTP client headers, reidirect policy and other
// HTTP settings, create a client.
func UseClient() {
	// Check "http://golang.org/pkg/net/http/#Client" for options. Here,
	// we are actually create a zero value client (the DefaultClient).
	client := &http.Client{}
	res, _ := client.Get("http://www.google.com/robots.txt")
	robots, _ := ioutil.ReadAll(res.Body)
	res.Body.Close()
	fmt.Println(robots)
}


func main() {
	UseGet()
	UseClient()
}
