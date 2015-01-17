package main

import (
	"crypto/tls"
	"fmt"
	"net/http"
	"time"

	"github.com/golang/glog"
)

func main() {
	server := &http.Server{
		Addr:           "0.0.0.0:9443",
		Handler:        http.HandlerFunc(handleClient),
		ReadTimeout:    5 * time.Minute,
		WriteTimeout:   5 * time.Minute,
		MaxHeaderBytes: 1 << 20,
		// Optional TLS config, used by ListenAndServeTLS.
		TLSConfig: &tls.Config{
			MinVersion: tls.VersionSSL30,
			ClientAuth: tls.RequestClientCert,
		},
	}
	if err := server.ListenAndServeTLS("ca1.crt.pem", "ca1.key.pem"); err != nil {
		glog.Errorf("Unable to listen for secure address: (%v).", err)
	}
}

func handleClient(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Inside helloHandler")
	fmt.Fprintf(w, "Hello from my TLS server!\n")
}
