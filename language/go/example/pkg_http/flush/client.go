package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"net/http"
)

// Test how flush could affect http connection, need to work with server.go.
func TestFlush() {
	client := &http.Client{}
	res, _ := client.Get("http://localhost:9999/flush")
	// IMPORTANT: Even though server is in busy loop, since the first
	// flusher.Flush() in server.go#flushHandler will respond to us, we
	// will return from Get. If there is no Flush at server side, we'll
	// never return from Get.
	fmt.Println("Returned from server:", res.Status)
	// IMPORTANT: However, we will wait for server to end transferring
	// body, so in this case, ReadAll() will be blocked for some time
	// until server loop returns. Alternatively, we can read line by
	// line from res.Body (which is a io.Reader) using Scanner.
	if false {
		robots, _ := ioutil.ReadAll(res.Body)
		fmt.Printf(string(robots))
	} else {
		scanner := bufio.NewScanner(res.Body)
		for scanner.Scan() {
			fmt.Println(scanner.Text())
		}
	}
	res.Body.Close()
}

func main() {
	TestFlush()
}
