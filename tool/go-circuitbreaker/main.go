package main

import (
	"errors"
	"fmt"
	"time"

	circuit "github.com/rubyist/circuitbreaker"
)

func main() {
	// Creates a circuit breaker that will trip if the function fails 5 times.
	cb := circuit.NewThresholdBreaker(5)

	events := cb.Subscribe()
	go func() {
		for {
			e := <-events
			// Monitor breaker events like BreakerTripped, BreakerReset, BreakerFail, BreakerReady
			switch e {
			case circuit.BreakerTripped:
				fmt.Println("Breaker tripped")
			case circuit.BreakerReset:
				fmt.Println("Breaker reset")
			case circuit.BreakerFail:
				fmt.Println("Breaker fail")
			case circuit.BreakerReady:
				fmt.Println("Breaker ready")
			}
		}
	}()

	counter := 0
	for {
		cb.Call(func() error {
			// This is where you'll do some remote call. If it fails, return an error.
			if counter < 8 {
				return nil
			} else {
				return errors.New("Error occurs")
			}
		}, 0)
		counter++
		time.Sleep(time.Second)
	}
}
