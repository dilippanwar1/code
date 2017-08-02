// The first example is a simplified version of an actual bug found by the
// race detector. It uses a timer to print a message after a random duration
// between 0 and 1 second. It does so repeatedly for five seconds. It uses
// time.AfterFunc to create a Timer for the first message and then uses the
// Reset method to schedule the next message, re-using the Timer each time.
//
// Run race detector with --race.
package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	racy()
	// fixed()
}

func racy() {
	start := time.Now()
	var t *time.Timer
	// AfterFunc waits for the duration to elapse and then calls f in its own
	// goroutine.
	t = time.AfterFunc(randomDuration(), func() {
		fmt.Println(time.Now().Sub(start))
		// RACE: an unsynchronized read and write of the variable t from different
		// goroutines. If the initial timer duration is very small, the timer
		// function may fire before the main goroutine has assigned a value to t
		// and so the call to t.Reset is made with a nil t.
		t.Reset(randomDuration())
	})
	time.Sleep(2 * time.Second)
}

func fixed() {
	start := time.Now()
	reset := make(chan bool)
	var t *time.Timer
	t = time.AfterFunc(randomDuration(), func() {
		fmt.Println(time.Now().Sub(start))
		reset <- true
	})
	for time.Since(start) < 2*time.Second {
		<-reset
		t.Reset(randomDuration())
	}
}

func randomDuration() time.Duration {
	return time.Duration(rand.Int63n(1e2))
}
