// Use InsecureSkipVerify so that we can communicate to bad server.
package main

import (
	"crypto/tls"
	"crypto/x509"
	"fmt"
	"io"
	"io/ioutil"
	"log"
)

func main() {
	cert_b, _ := ioutil.ReadFile("../certs.d/client_cert1.crt")
	priv_b, _ := ioutil.ReadFile("../certs.d/client_cert1.key")
	priv, _ := x509.ParsePKCS1PrivateKey(priv_b)

	// TLS Client Configuration.
	config := tls.Config{
		Certificates: []tls.Certificate{
			tls.Certificate{
				Certificate: [][]byte{cert_b},
				PrivateKey:  priv,
			},
		},
		// InsecureSkipVerify controls whether a client verifies the server's certificate
		// chain and host name. If InsecureSkipVerify is true, TLS accepts any certificate
		// presented by the server and any host name in that certificate. This is useful
		// for testing, e.g. self-signed certificate.
		InsecureSkipVerify: true,
	}

	conn, err := tls.Dial("tcp", "127.0.0.1:9443", &config)
	if err != nil {
		log.Fatalf("client: dial: %s", err)
	}
	defer conn.Close()
	log.Println("client: connected to: ", conn.RemoteAddr())

	// Get basic TLS details about the established connection.
	state := conn.ConnectionState()
	for _, v := range state.PeerCertificates {
		fmt.Println(v.Subject)
	}
	log.Println("client: handshake: ", state.HandshakeComplete)
	log.Println("client: mutual: ", state.NegotiatedProtocolIsMutual)

	message := "Hello\n"
	n, err := io.WriteString(conn, message)
	if err != nil {
		log.Fatalf("client: write: %s", err)
	}
	log.Printf("client: wrote %q (%d bytes)", message, n)

	reply := make([]byte, 256)
	n, err = conn.Read(reply)
	log.Printf("client: read %q (%d bytes)", string(reply[:n]), n)
	log.Print("client: exiting")
}
