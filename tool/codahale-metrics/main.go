package main

import (
	"fmt"
	"net/http"

	"github.com/codahale/metrics"
)

func main() {
	// metrics.Counter is type of string, here we convert "request_count" to
	// type metrics.Counter.
	metrics.Counter("request_count").Add()
	metrics.Gauge("memory_stats").Set(102)

	// hdrhistogram gives the percentage of values under specific value.
	histogram := metrics.NewHistogram("learning", 0, 100, 1)
	histogram.RecordValue(25)
	histogram.RecordValue(80)

	// Visit the metrics through "/debug/vars" endpoint. (codahale's metrics
	// is just a wrapper of golang expvar.
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprint(w, "hello gophers")
	})
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		panic(err)
	}
}
