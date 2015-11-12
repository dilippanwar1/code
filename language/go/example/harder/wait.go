package main

import (
	"errors"
	"fmt"
	"time"
)

func main() {
	condition := func() (done bool, err error) {
		fmt.Println("Condition is called")
		return false, nil
	}

	err := Poll(time.Second, 10*time.Second, condition)
	fmt.Printf("Done: %v", err)
}

// WaitFunc creates a channel that receives an item every time a test
// should be executed and is closed when the last test should be invoked.
type WaitFunc func(done <-chan struct{}) <-chan struct{}

// ConditionFunc returns true if the condition is satisfied, or an error
// if the loop should be aborted.
type ConditionFunc func() (done bool, err error)

// Poll tries a condition func until it returns true, an error, or the timeout
// is reached. condition will always be invoked at least once but some intervals
// may be missed if the condition takes too long or the time window is too short.
// If you want to Poll something forever, see PollInfinite.
// Poll always waits the interval before the first check of the condition.
func Poll(interval, timeout time.Duration, condition ConditionFunc) error {
	done := make(chan struct{})
	defer close(done)
	return waitfor(poller(interval, timeout), condition, done)
}

// poller returns a WaitFunc. The wait function sends signal to its returned
// channel every 'interval', and close the channel after 'timeout'.
func poller(interval, timeout time.Duration) WaitFunc {
	return WaitFunc(func(done <-chan struct{}) <-chan struct{} {
		ch := make(chan struct{})

		go func() {
			defer close(ch)

			t := time.NewTicker(interval)
			var after *time.Timer
			if timeout != 0 {
				after = time.NewTimer(timeout)
				defer after.Stop()
			}

			for {
				select {
				case <-done:
					return
				case <-after.C:
					return
				case <-t.C:
					ch <- struct{}{}
				}
			}
		}()
		return ch
	})
}

// Waitfor waits for a condition (as in parameter 'fn') to become true. Instead
// of polling forever, it gets a channel from wait(), and then invokes 'fn' once
// for every value placed on the channel and once more when the channel is closed.
func waitfor(wait WaitFunc, fn ConditionFunc, done <-chan struct{}) error {
	c := wait(done)
	for {
		// Block until we have a signal from wait, or channel is closed.
		_, open := <-c
		ok, err := fn()
		if err != nil {
			return err
		}
		if ok {
			return nil
		}
		if !open {
			return errors.New("Timeout waiting for condition")
		}
	}
}
