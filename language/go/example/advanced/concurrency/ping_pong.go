package main

import (
	"fmt"
	"time"
)

type Ball struct {
	hit int
}

func main() {
	ball_chan := make(chan *Ball)
	go player("ping", ball_chan)
	go player("pong", ball_chan)

	ball_chan <- new(Ball) // game start
	time.Sleep(time.Second)
	<-ball_chan
}

func player(message string, ball_chan chan *Ball) {
	for {
		ball := <-ball_chan // catch the ball
		ball.hit++
		fmt.Println(message, ball.hit)
		ball_chan <- ball // toss the ball
		time.Sleep(50 * time.Millisecond)
	}
}
