package main

import (
	"fmt"
	"net/http"
	"os"
	"time"

	"gopkg.in/tylerb/graceful.v1"
)

func handler(w http.ResponseWriter, r *http.Request) {
	duration, err := time.ParseDuration(r.FormValue("duration"))
	if err != nil {
		http.Error(w, err.Error(), 400)
		return
	}
	fmt.Fprintf(w, "going to sleep %s with pid %d\n", duration, os.Getpid())
	w.(http.Flusher).Flush()
	time.Sleep(duration)
	fmt.Fprintf(w, "slept %s with pid %d\n", duration, os.Getpid())
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/sleep/", func(w http.ResponseWriter, r *http.Request) {
		duration, err := time.ParseDuration(r.FormValue("duration"))
		if err != nil {
			http.Error(w, err.Error(), 400)
			return
		}
		time.Sleep(duration)
		fmt.Fprintf(
			w,
			"%s started at %s slept for %d nanoseconds from pid %d.\n",
			"demo",
			time.Now(),
			duration.Nanoseconds(),
			os.Getpid(),
		)
	})

	graceful.Run(":3001", 30*time.Second, mux)
}
