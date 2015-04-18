package main

// Go provides a `flag` package supporting basic command-line flag parsing.
// Note that the flag package requires all flags to appear before positional
// arguments (otherwise the flags will be interpreted as positional arguments).
import (
	"errors"
	"flag"
	"fmt"
	"strings"
	"time"
)

// A user-defined flag type, a slice of durations.
type interval []time.Duration

// String is the method to format the flag's value, part of the flag.Value
// interface. The String method's output will be used in diagnostics.
func (i *interval) String() string {
	return fmt.Sprint(*i)
}

// Set is another part of the flag.Value interface. Command line value will
// be passed to the method, and it is responsible to parse the value then
// stores it in the receiver (here, pointer *i).
func (i *interval) Set(value string) error {
	if len(*i) > 0 {
		return errors.New("interval flag already set")
	}

	for _, dt := range strings.Split(value, ",") {
		duration, err := time.ParseDuration(dt)
		if err != nil {
			return err
		}
		*i = append(*i, duration)
	}
	return nil
}

func main() {
	// Basic flag declarations are available for string, integer, and boolean
	// options. Here we declare a string flag `word` with a default value "foo"
	// and a short description. This `flag.String` function returns a string
	// pointer (not a string value); we'll see how to use this pointer below.
	wordPtr := flag.String("word", "foo", "a string")

	// This declares `numb` and `fork` flags, using a similar approach to the
	// `word` flag.
	numbPtr := flag.Int("numb", 42, "an int")
	boolPtr := flag.Bool("fork", false, "a bool")

	// It's also possible to declare an option that uses an existing var
	// declared elsewhere in the program. Note that we need to pass in a
	// pointer to the flag declaration function.
	var svar string
	flag.StringVar(&svar, "svar", "bar", "a string var")

	// Define a flag to accumulate durations.
	var intervalFlag interval
	flag.Var(&intervalFlag, "deltaT", "Comma-separated list of intervals to use.")

	// Once all flags are declared, call `flag.Parse()` to execute the
	// command-line parsing.
	flag.Parse()

	// Here we'll just dump out the parsed options and any trailing positional
	// arguments. Note that we need to dereference the points with e.g. `*wordPtr`
	// to get the actual option values.
	// E.g. go run pkg_flag.go --word=wtf --deltaT=1h,2h,20m
	fmt.Println("word:", *wordPtr)         // wtf
	fmt.Println("numb:", *numbPtr)         // 42
	fmt.Println("fork:", *boolPtr)         // false
	fmt.Println("svar:", svar)             // bar
	fmt.Println("interval:", intervalFlag) // [1h0m0s 2h0m0s 20m0s]

	fmt.Println("Tail arguments:", flag.Args())
}
