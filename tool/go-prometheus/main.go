package main

import (
	"net/http"

	"github.com/prometheus/client_golang/prometheus"
)

var (
	indexed = prometheus.NewCounter(prometheus.CounterOpts{
		Namespace: "my_company",
		Subsystem: "indexer",
		Name:      "documents_indexed",
		Help:      "The number of documents indexed.",
	})
	size = prometheus.NewGauge(prometheus.GaugeOpts{
		Namespace: "my_company",
		Subsystem: "storage",
		Name:      "documents_total_size_bytes",
		Help:      "The total size of all documents in the storage.",
	})
	requests = prometheus.NewCounterVec(
		prometheus.CounterOpts{
			Name: "server_request_count",
			Help: "Counter of server requests broken by verb",
		},
		[]string{"verb"})
)

func main() {
	indexed.Inc()
	size.Set(5)

	// See metrics at 'localhost:8080/metrics'.  Send request to 'localhost:8080/request'
	// and observe 'server_request_count' metric.
	http.Handle("/metrics", prometheus.Handler())
	http.Handle("/request", http.HandlerFunc(func(writer http.ResponseWriter, req *http.Request) {
		requests.WithLabelValues(req.Method).Inc()
	}))

	http.ListenAndServe(":8080", nil)
}

func init() {
	prometheus.MustRegister(indexed)
	prometheus.MustRegister(size)
	prometheus.MustRegister(requests)
}
