package main

import (
	"fmt"
	"sync"
	"time"
)

// gen converts a list of integers to a channel, and close the
// channel when all integers are sent.
func gen(done chan bool, input ...int) chan int {
	c := make(chan int)
	go func() {
		defer close(c)
		for _, num := range input {
			select {
			case c <- num:
				fmt.Println("Sent number in gen", num)
			case <-done:
				fmt.Println("gen exits")
				return
			}
		}
		fmt.Println("gen finished")
	}()
	return c
}

// square receives integer from input channel, square it and
// send it to output channel. It returns the output channel for
// next stage.
func square(done chan bool, input <-chan int) chan int {
	c := make(chan int)
	go func() {
		defer close(c)
		for num := range input {
			select {
			case c <- num * num:
				fmt.Println("Sent number in square", num*num)
			case <-done:
				fmt.Println("square exits")
				return
			}
		}
	}()
	return c
}

// merge takes a list of channels to read input from, and send
// result to the single output channel.
func merge(done chan bool, cs ...chan int) chan int {
	c := make(chan int)

	var wg sync.WaitGroup
	wg.Add(len(cs))

	for _, input := range cs {
		go func(input chan int) {
			defer wg.Done()
			for num := range input {
				select {
				case c <- num:
					fmt.Println("Sent number in merge", num)
				case <-done:
					fmt.Println("merge exits")
					return
				}
			}
		}(input) // Be careful about the input param here.
	}

	go func() {
		wg.Wait()
		close(c)
	}()

	return c
}

func main() {
	// Instead of sending done to upstream stage, set up a done channel
	// that's shared by the whole pipeline, and close that channel when
	// this pipeline exits, as a signal for all the goroutines we started
	// to exit.
	done := make(chan bool)

	in := gen(done, 2, 3)
	// Distribute the sq work across two goroutines that both read from in.
	c1 := square(done, in)
	c2 := square(done, in)

	// Consume the merged output from c1 and c2.
	fmt.Println(<-merge(done, c1, c2))
	close(done)

	time.Sleep(2 * time.Second)
}
