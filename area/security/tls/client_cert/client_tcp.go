// Use client_cert1.crt will be accpeted by server, as it's signed by server trusted CA.
// Use client_cert2.crt will be rejected by server, as it's not signed by server trusted CA.
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
	cert2_b, _ := ioutil.ReadFile("../certs.d/client_cert1.crt")
	priv2_b, _ := ioutil.ReadFile("../certs.d/client_cert1.key")
	priv2, _ := x509.ParsePKCS1PrivateKey(priv2_b)

	// TLS Client Configuration.
	config := tls.Config{
		Certificates: []tls.Certificate{
			tls.Certificate{
				Certificate: [][]byte{cert2_b},
				PrivateKey:  priv2,
			},
		},
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
