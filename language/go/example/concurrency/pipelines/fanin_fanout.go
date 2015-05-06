package main

import (
	"fmt"
	"sync"
)

// gen converts a list of integers to a channel, and close the
// channel when all integers are sent.
func gen(input ...int) chan int {
	c := make(chan int)
	go func() {
		for _, num := range input {
			c <- num
		}
		close(c)
	}()
	return c
}

// square receives integer from input channel, square it and
// send it to output channel. It returns the output channel for
// next stage.
func square(input <-chan int) chan int {
	c := make(chan int)
	go func() {
		for num := range input {
			c <- num * num
		}
		close(c)
	}()
	return c
}

// merge takes a list of channels to read input from, and send
// result to the single output channel.
func merge(cs ...chan int) chan int {
	c := make(chan int)

	var wg sync.WaitGroup
	wg.Add(len(cs))

	for _, input := range cs {
		go func(input chan int) {
			for num := range input {
				c <- num
			}
			wg.Done()
		}(input) // Be careful about the input param here.
	}

	go func() {
		wg.Wait()
		close(c)
	}()

	return c
}

func main() {
	in := gen(2, 3)

	// Distribute the sq work across two goroutines that both read from in.
	c1 := square(in)
	c2 := square(in)

	// Consume the merged output from c1 and c2.
	for n := range merge(c1, c2) {
		fmt.Println(n) // 4 then 9, or 9 then 4
	}
}
