package main

import "fmt"

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

func main() {
	c := gen(2, 3)
	c = square(c)

	for num := range c {
		fmt.Println(num)
	}

	// We can create the pipeline with multiple 'square'.
	c = square(square(gen(2, 3)))
	for num := range c {
		fmt.Println(num)
	}
}
