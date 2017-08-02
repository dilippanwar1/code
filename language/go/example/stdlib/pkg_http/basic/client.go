package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

// Use Get method in http package directy, it is a wrapper around
// DefaultClient.Get(), i.e. http.Get == http.DefaultClieng.Get().
func UseDefaultClient() {
	res, err := http.Get("http://www.google.com/robots.txt")
	if err != nil {
		log.Fatal(err)
	}

	// ReadAll reads from r until an error or EOF.
	robots, err := ioutil.ReadAll(res.Body)
	if err != nil {
		log.Fatal(err)
	}

	// Client must close body when finish with it.
	res.Body.Close()

	fmt.Println(len(robots))
}

// For control over HTTP client headers, reidirect policy and other
// HTTP settings, create a client.
func UseOwnClient() {
	// Check "http://golang.org/pkg/net/http/#Client" for options. Here,
	// we are actually create a zero value client (the DefaultClient).
	client := &http.Client{}
	res, _ := client.Get("http://www.google.com/robots.txt")
	robots, _ := ioutil.ReadAll(res.Body)
	res.Body.Close()
	fmt.Println(len(robots))
}

// More control over HTTP configs using Request object.
func UseDo() {
	client := &http.Client{}
	req, _ := http.NewRequest("GET", "http://www.google.com/robots.txt", nil)
	req.Header.Add("User-Agent", "Gobook Custom User-Agent")
	res, _ := client.Do(req)
	robots, _ := ioutil.ReadAll(res.Body)
	res.Body.Close()
	fmt.Println(len(robots))
}

func main() {
	UseDefaultClient()
	UseOwnClient()
	UseDo()
}
