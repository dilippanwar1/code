package main

import (
	"time"

	rss "github.com/jteeuwen/go-pkg-rss"
)

// newFetcher creates a new Fetcher that fetches items from given domain.
func newFetcher(domain string) Fetcher {
	return &fetcher{
		domain: domain,
	}
}

type fetcher struct {
	domain string
}

// Fetch implements Fetcher interface.
func (f *fetcher) Fetch() ([]Item, time.Time, error) {
	feed := rss.New(timeout, true, chanHandler, itemHandler)

	items := []Item{
		{Title: f.domain},
	}
	return items, time.Now(), nil
}
