// Simple https client connect to server_https.go, can also just do:
//   $ curl -k https://127.0.0.1:9443
// Note '-k' is required to skip the warning of self-signed certificate.
package main

import (
	"bufio"
	"crypto/tls"
	"fmt"
	"net/http"
)

func main() {
	tr := &http.Transport{
		TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
	}
	client := &http.Client{Transport: tr}
	res, err := client.Get("https://localhost:9443/")
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println("Returned from server:", res.Status)
	scanner := bufio.NewScanner(res.Body)
	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}
	res.Body.Close()
}
