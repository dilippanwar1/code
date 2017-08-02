package main

import "fmt"

func main() {
	var a []int
	var c, c1, c2, c3, c4 chan int
	var i1, i2 int

	// Demonstration for various syntaxes.
	select {
	case i1 = <-c1:
		print("received ", i1, " from c1\n")
	case c2 <- i2:
		print("sent ", i2, " to c2\n")
	case i3, ok := (<-c3): // same as: i3, ok := <-c3
		if ok {
			print("received ", i3, " from c3\n")
		} else {
			print("c3 is closed\n")
		}
	case a[f()] = <-c4:
		// same as:
		// case t := <-c4
		//	a[f()] = t
	default:
		print("no communication\n")
	}

	c = make(chan int)
	go func() {
		for {
			fmt.Println(<-c)
		}
	}()
	for i := 0; i < 5; i++ { // send random sequence of bits to c
		select {
		case c <- 0: // note: no statement, no fallthrough, no folding of cases
		case c <- 1:
		}
	}

	// In select, trying to read/write at the same time won't work; the
	// code prints "No activity".
	chan_1 := make(chan int)
	select {
	case chan_1 <- 1:
		fmt.Println("Sent")
	case <-chan_1:
		fmt.Println("Read")
	default:
		fmt.Println("No activity")
	}

	// Note expressions appear in case will be evaluated before channel
	// send or receive.
	ch := make(chan int)
	go func() {
		select {
		case ch <- DoSometing(): // DoSomething will be called.
		default:
		}
	}()
	fmt.Println(<-ch)
}

func DoSometing() int {
	fmt.Println("Am I evaluated?")
	return 1
}

func f() int { return 0 }
