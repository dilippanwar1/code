package main

import "time"

type Item struct {
	Title, Channel, GUID string // a subset of RSS fields
}

type Fetcher interface {
	Fetch() ([]Item, time.Time, error)
}

type Subscription interface {
	Updates() <-chan Item // stream of Items
	Close() error         // shuts down the subscription
}
