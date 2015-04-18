package main

import "fmt"

type Request struct {
	args []int
	f    func([]int) int
	ch   chan int
}

// Server
func Serve(queue chan *Request) {
	for req := range queue {
		req.ch <- req.f(req.args)
	}
}

// Client
func sum(a []int) int {
	s := 0
	for _, v := range a {
		s += v
	}
	return s
}

func main() {
	queue := make(chan *Request, 5)

	// Server
	go Serve(queue)

	// Client
	request := &Request{[]int{3, 4, 5}, sum, make(chan int)}
	// Send request
	queue <- request
	// Wait for response.
	fmt.Printf("answer: %d\n", <-request.ch)
}
