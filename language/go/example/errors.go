package main

import (
	"errors"
	"fmt"
)

// Basic usage 1:
// Note by convention, errors are the last return value and have type
// error, which is a builtin interface. An 'error' variable represents
// any value that can describe itself as a string.
//   type error interface {
//     Error() string
//   }
func f1(arg int) (int, error) {
	if arg == 42 {
		// 'errors.New' construct a basic 'error' value.
		return -1, errors.New("Can't work with 43")
	}
	// A nil value means no error.
	return arg + 3, nil
}

// Basic usage 2:
// It's possible to use custom types as errors by implementing
// the Error() method on them.
type ArgError struct {
	arg int
	msg string
}

func (e *ArgError) Error() string {
	return fmt.Sprintf("%d - %s", e.arg, e.msg)
}

func f2(arg int) (int, error) {
	if arg == 42 {
		return -1, &ArgError{arg, "can't work with it"}
	}
	return arg + 3, nil
}

func main() {

	for _, i := range []int{7, 42} {
		if r, e := f1(i); e != nil {
			fmt.Println("f1 failed:", e)
		} else {
			fmt.Println("f1 worked:", r)
		}
	}

	for _, i := range []int{7, 42} {
		if r, e := f2(i); e != nil {
			fmt.Println("f2 failed:", e)
		} else {
			fmt.Println("f2 worked:", r)
		}
	}

	// 'e' is a pointer to struct ArgError. If you want to programmatically
	// use the data in a custom error, you’ll need to get the error as an
	// instance of the custom error type via type assertion.
	_, e := f2(42)
	if ae, ok := e.(*ArgError); ok {
		fmt.Println(ae.arg)
		fmt.Println(ae.msg)
	}
}
