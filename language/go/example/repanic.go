// If doParse panics, the recovery block will set the return value to
// nil—deferred functions can modify named return values. It will then
// check, in the assignment to err, that the problem was a parse error
// by asserting that it has the local type Error. If it does not, the
// type assertion will fail, causing a run-time error that continues
// the stack unwinding as though nothing had interrupted it. This check
// means that if something unexpected happens, such as an index out of
// bounds, the code will fail even though we are using panic and recover
// to handle parse errors.

package main

import "fmt"

// Error is the type of a parse error; it satisfies the error interface.
type Error string

func (e Error) Error() string {
	return string(e)
}

type Regexp struct{}

// error is a method of *Regexp that reports parsing errors by
// panicking with an Error.
func (regexp *Regexp) error(err string) {
	panic(Error(err))
}

func (regexp *Regexp) doParse(str string) *Regexp {
	if str[0] == '*' {
		regexp.error("'*' illegal at start of expression")
	}
	return regexp
}

// Compile returns a parsed representation of the regular expression.
func Compile(str string) (regexp *Regexp, err error) {
	regexp = new(Regexp)

	defer func() {
		if e := recover(); e != nil {
			regexp = nil
			err = e.(Error) // Will repanic if error is not from doParse.
			fmt.Println(err)
		}
	}()
	return regexp.doParse(str), nil
}

func main() {
	Compile("*sf")
}
