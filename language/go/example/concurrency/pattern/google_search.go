package main

import (
	"fmt"
	"math/rand"
	"time"
)

var (
	Web   = fakeSearch("web")
	Image = fakeSearch("image")
	Video = fakeSearch("video")
)

type Result string
type Search func(query string) Result

func fakeSearch(kind string) Search {
	return func(query string) Result {
		time.Sleep(time.Duration(rand.Intn(100)) * time.Millisecond)
		return Result(fmt.Sprintf("%s result for %q\n", kind, query))
	}
}

// First is a util that takes a query string, a list of Search interface, and
// return first result from all of the replicas.
func First(query string, replicas ...Search) Result {
	c := make(chan Result)
	searchReplica := func(i int) { c <- replicas[i](query) }
	for i := range replicas {
		go searchReplica(i)
	}
	return <-c
}

func Google_v1(query string) (results []Result) {
	results = append(results, Web(query))
	results = append(results, Image(query))
	results = append(results, Video(query))
	return
}

func Google_v2(query string) (results []Result) {
	c := make(chan Result)
	go func() { c <- Web(query) }()
	go func() { c <- Image(query) }()
	go func() { c <- Video(query) }()

	// Launch concurrently, so we only wait for slowest.
	for i := 0; i < 3; i++ {
		results = append(results, <-c)
	}
	return results
}

// Add timeout to v2.
func Google_v2_1(query string) (results []Result) {
	c := make(chan Result)
	go func() { c <- Web(query) }()
	go func() { c <- Image(query) }()
	go func() { c <- Video(query) }()

	timeout := time.Duration(50 * time.Millisecond)
	// Launch concurrently, so we only wait for slowest.
	for i := 0; i < 3; i++ {
		select {
		case result := <-c:
			results = append(results, result)
		case <-time.After(timeout):
			fmt.Println("Timeout!!")
		}
	}
	return results
}

// Do not discard the slowest one, instead, run multiple replicas.
func Google_v3(query string) (results []Result) {
	c := make(chan Result)
	go func() { c <- First(query, Web, Web) }()
	go func() { c <- First(query, Image, Image) }()
	go func() { c <- First(query, Video, Video) }()

	timeout := time.Duration(50 * time.Millisecond)
	// Launch concurrently, so we only wait for slowest.
	for i := 0; i < 3; i++ {
		select {
		case result := <-c:
			results = append(results, result)
		case <-time.After(timeout):
			fmt.Println("Timeout!!")
		}

	}
	return results
}

func main() {
	rand.Seed(time.Now().UnixNano())
	start := time.Now()
	results := Google_v3("golang")
	elapsed := time.Since(start)
	fmt.Println(results)
	fmt.Println(elapsed)
}
