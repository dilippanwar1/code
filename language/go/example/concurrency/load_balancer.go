package main

import (
	"fmt"
	"sort"
	"time"
)

type Request struct {
	workFn func() int // The operation to perform.
	result chan int   // The channel to receive result.
}

// Requester send fake requests to the given channel. Results are collected
// directly instead of going through load balancer.
func Requester(worker chan *Request) {
	WorkHard := func() int {
		fmt.Println("I'm working hard")
		time.Sleep(time.Second)
		return 8
	}
	result := make(chan int)
	for {
		// Wait for some time and send request.
		time.Sleep(time.Second)
		worker <- &Request{WorkHard, result}
		fmt.Println("Get response:", <-result)
	}
}

// Worker represents a single worker.
type Worker struct {
	UUID    int           // ID of the worker
	work    chan *Request // The work to do.
	pending int           // The number of pending tasks.
}

// Work takes a 'done' channel to notify load balancer that work is done.
// Worker receives work from its 'work' channel.
func (worker *Worker) Work(done chan<- *Worker) {
	for {
		req := <-worker.work
		fmt.Println("worker", worker.UUID, "starts working...")
		req.result <- req.workFn()
		fmt.Println("worker", worker.UUID, "sending done...")
		done <- worker
		fmt.Println("worker", worker.UUID, "sent done...")
	}
}

type Pool []*Worker

func (p Pool) Less(i, j int) bool {
	return p[i].pending < p[j].pending
}

func (p Pool) Len() int {
	return len(p)
}

func (p Pool) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

type LoadBalancer struct {
	pool Pool // A pool of workers
	done chan *Worker
}

func (lb *LoadBalancer) Balance(request chan *Request) {
	// Launch all workers.
	for _, worker := range lb.pool {
		go worker.Work(lb.done)
	}
	// Note the following for loop won't work. If we have more requests
	// than worker and requests come more frequent than worker, then
	// load balancer will block on dispatch and will never be able to
	// receive lb.done.
	// for {
	// 	select {
	// 	case req := <-request:
	// 		lb.dispatch(req)
	// 	case work := <-lb.done:
	// 		lb.complete(work)
	// 	}
	// }
	go func() {
		for {
			lb.dispatch(<-request)
		}
	}()
	go func() {
		for {
			lb.complete(<-lb.done)
		}
	}()
}

func (lb *LoadBalancer) dispatch(req *Request) {
	sort.Sort(lb.pool)
	worker := lb.pool[0]
	worker.work <- req
	worker.pending++
}

func (lb *LoadBalancer) complete(worker *Worker) {
	fmt.Println("worker", worker.UUID, "complete")
	worker.pending--
}

func main() {
	request := make(chan *Request)
	lb := LoadBalancer{
		pool: []*Worker{
			&Worker{UUID: 1, work: make(chan *Request), pending: 0},
			&Worker{UUID: 2, work: make(chan *Request), pending: 0},
			&Worker{UUID: 3, work: make(chan *Request), pending: 0},
			&Worker{UUID: 4, work: make(chan *Request), pending: 0},
		},
		done: make(chan *Worker),
	}

	go lb.Balance(request)

	for i := 0; i < 10; i++ {
		go Requester(request)
	}

	time.Sleep(10 * time.Second)
}
