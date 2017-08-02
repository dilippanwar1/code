package main

import (
	"fmt"
	"sync"
	"time"
)

const GameDuration = 5 * time.Second
const GameInterval = 1 * time.Second

var messages []string = []string{"菜鸟都能用的云!", "HaHa", "HuoHuo"}

func main() {
	action := make(chan struct{})
	quit := make(chan struct{})

	wg := sync.WaitGroup{}
	wg.Add(len(messages))
	for i := 0; i < len(messages); i++ {
		go func(i int) {
			for {
				select {
				case <-action:
					fmt.Printf("%d%s!\n", i, messages[i])
				case <-quit:
					fmt.Printf("%d Done!\n", i)
					wg.Done()
					return
				}
			}
		}(i)
	}

	interval := time.NewTicker(GameInterval)
	duration := time.NewTicker(GameDuration)

	go func() {
		for {
			select {
			case <-interval.C:
				action <- struct{}{}
			case <-duration.C:
				duration.Stop()
				interval.Stop()
				close(quit)
			}
		}
	}()

	wg.Wait()
}
