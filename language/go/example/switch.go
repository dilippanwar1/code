package main

import (
	"fmt"
	"time"
)

func main() {
	i := 2
	fmt.Print("write ", i, " as ")

	// Note that 'break' is by default.
	switch i {
	case 1:
		fmt.Println("one")
	case 2:
		fmt.Println("two")
	case 3:
		fmt.Println("three")
	}

	// You can use commas to separate multiple expressions in the same case
	// statement. We use the optional default case in this example as well.
	switch time.Now().Weekday() {
	case time.Saturday, time.Sunday:
		fmt.Println("it's the weekend")
	default:
		fmt.Println("it's a weekday")
	}

	// switch without an expression is an alternate way to express if/else
	// logic. Here we also show how the case expressions can be non-constants.
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("it's before noon")
	default:
		fmt.Println("it's after noon")
	}

	// Only the first match will be executed, it is essentially if..elseif.
	switch {
	case i > 1:
		fmt.Println("i > 1")
	case i < 3:
		fmt.Println("i < 3")
	default:
		fmt.Println("i ?")
	}

	// There is no automatically fall through, to achieve that, use
	// comma-sepparated lists.
	c := "?"
	switch c {
	case ".", "?", "*":
		fmt.Println("Got it")
	default:
		fmt.Println("In vain")
	}

	i = 0
L:
	for ; i < 10; i++ {
		switch i {
		case 2:
			// This break will break out the for loop. Use 'break' without
			// the L tag won't work (it will break out the switch, so the
			// loop will continue).
			break L
		}
	}
	fmt.Println(i) // 2
}
