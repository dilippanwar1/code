// Golang HTML5 Server Sent Events Example
//
// Origin: https://github.com/kljensen/golang-html5-sse-example
//
// Run with:
//   $ go run sse-server.go
//
// Then browse to http://localhost:8000. Browser must support HTML5 SSE, if not,
// then use polyfill client, e.g. https://github.com/Yaffle/EventSource
package main

import (
	"fmt"
	"log"
	"net/http"
	"text/template"
	"time"
)

// Broker is responsible for keeping a list of which clients (browsers) that are
// currently attached and broadcasting events (messages) to those clients.
type Broker struct {
	// clients is a map of clients - a client is a channel which accepts a string payload.
	// The value type is bool, which is meaning less.
	clients map[chan string]bool

	// newClients is channel of client (a channel) - HTTP handler sends new client in and
	// broker reads it out.
	newClients chan chan string

	// defunctClients is also a channel of client.
	defunctClients chan chan string

	// messages is a channel of strings - new event (message) will be pushed to the channal
	// by other part of the system; broker reads it out and sends to clients.
	messages chan string
}

// This Broker method starts a new goroutine.  It handles the addition & removal
// of clients, as well as the broadcasting of messages out to clients that are
// currently attached.
func (b *Broker) Start() {
	go func() {
		for {
			select {
			case newClient := <-b.newClients:
				b.clients[newClient] = true
				log.Println("Broker added new client")

			case defunctClient := <-b.defunctClients:
				delete(b.clients, defunctClient)
				close(defunctClient)
				log.Println("Broker deleted client")

			case message := <-b.messages:
				for client, _ := range b.clients {
					client <- message
				}
				log.Printf("Broker sent broadcast message to %d clients\n", len(b.clients))
			}
		}
	}()
}

// This Broker method handles and HTTP request at the "/events/" URL.
func (b *Broker) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	// Make sure that the writer supports flushing.
	f, ok := w.(http.Flusher)
	if !ok {
		http.Error(w, "Streaming unsupported!", http.StatusInternalServerError)
		return
	}

	// Create a new channel, over which the broker can send this client messages.
	client := make(chan string)
	b.newClients <- client

	// Listen to connection close and un-register messageChan
	notify := w.(http.CloseNotifier).CloseNotify()
	go func() {
		<-notify
		b.defunctClients <- client
		log.Println("HTTP connection just closed.")
	}()

	// Set the headers related to event streaming.
	w.Header().Set("Content-Type", "text/event-stream")
	w.Header().Set("Cache-Control", "no-cache")
	w.Header().Set("Connection", "keep-alive")

	for {
		// Read from our message channel.
		msg, open := <-client
		if !open {
			// If our message channel was closed, this means that the client has disconnected.
			break
		}
		// Write to the ResponseWriter, `w`.
		fmt.Fprintf(w, "data: Message: %s\n\n", msg)
		// Flush the response.  This is only possible if the repsonse supports streaming.
		f.Flush()
	}

	log.Println("Finished HTTP request at ", r.URL.Path)
}

// Handler for the main page, which we wire up to the route at "/" below in `main`.
func MainPageHandler(w http.ResponseWriter, r *http.Request) {

	// Did you know Golang's ServeMux matches only the
	// prefix of the request URL?  It's true.  Here we
	// insist the path is just "/".
	if r.URL.Path != "/" {
		w.WriteHeader(http.StatusNotFound)
		return
	}

	// Read in the template with our SSE JavaScript code.
	t, err := template.ParseFiles("index.html")
	if err != nil {
		log.Fatal("WTF dude, error parsing your template.")
	}

	// Render the template, writing to `w`.
	t.Execute(w, "Duder")

	// Done.
	log.Printf("Finished HTTP request at %v", r.URL.Path)
}

// Main routine.
func main() {
	// Make a new Broker instance.
	b := &Broker{
		make(map[chan string]bool),
		make(chan (chan string)),
		make(chan (chan string)),
		make(chan string),
	}

	// Start processing events.
	b.Start()

	// Make 'Broker' the HTTP handler for "/events/".  It can do this because it has
	// a ServeHTTP method.  That method is called in a separate goroutine for each
	// request to "/events/".
	http.Handle("/events/", b)

	// Generate a constant stream of events that get pushed into the Broker's messages
	// channel and are then broadcast out to any clients that are attached.
	go func() {
		for i := 0; ; i++ {
			// Create a little message to send to clients, including the current time.
			b.messages <- fmt.Sprintf("%d - the time is %v", i, time.Now())
			// Print a nice log message and sleep for 5s.
			log.Printf("Generated message %d\n", i)
			time.Sleep(5 * 1e9)
		}
	}()

	// When we get a request at "/", call `MainPageHandler` in a new goroutine.
	http.Handle("/", http.HandlerFunc(MainPageHandler))
	// Start the server and listen forever on port 8000.
	http.ListenAndServe(":8000", nil)
}
