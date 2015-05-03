package main

// Subscribe creates a new Subscription that repeatedly fetches items until Close is called.
func Subscribe(fetcher Fetcher) Subscription {
	s := sub{
		fetcher: fetcher,
		updates: make(chan Item),
	}
	go s.loop()
	return s
}

// Merges merges several subscriptions.
func Merge(subs ...Subscription) Subscription {
}

// sub implements the Subscription interface.
type sub struct {
	fetcher Fetcher   // fetches items
	updates chan Item // delivers items to the user
}

func (s *sub) Updates() <-chan Item {
	return s.updates
}

func (s *sub) Close() error {
	Close(s.updates)
}

// loop fetches items using s.fetcher and sends them
// on s.updates.  loop exits when s.Close is called.
func (s *sub) loop() {}

func main() {

}
