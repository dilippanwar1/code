package main

import (
	"bufio"
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

// Test how flush could affect http connection, should work
// with pkg_http_server.go.
func TestFlush() {
	client := &http.Client{}
	res, _ := client.Get("http://localhost:9999/flush")
	// IMPORTANT: Even though server is in busy loop, since the first
	// flusher.Flush() in pkg_http_server.go#flushHandler will respond
	// to us, we will return from Get. If there is no Flush at server
	// side, we'll never return from Get.
	fmt.Println("Returned from server:", res.Status)
	// IMPORTANT: However, we will wait for server to end transfering
	// body, so in this case, ReadAll() will be blocked for some time
	// until server loop returns. Alternatively, we can read line by
	// one from res.Body (which is a io.Reader) using Scanner.
	// robots, _ := ioutil.ReadAll(res.Body)
	scanner := bufio.NewScanner(res.Body)
	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}
	res.Body.Close()
}

func main() {
	// UseGet()
	// UseClient()
	TestFlush()
}
