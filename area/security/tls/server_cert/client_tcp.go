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

	// The client trust ca.crt.
	ca_b, _ := ioutil.ReadFile("../certs.d/ca.crt")
	ca, _ := x509.ParseCertificate(ca_b)
	pool := x509.NewCertPool()
	pool.AddCert(ca)

	// TLS Client Configuration.
	config := tls.Config{
		Certificates: []tls.Certificate{
			tls.Certificate{
				Certificate: [][]byte{cert_b},
				PrivateKey:  priv,
			},
		},
		RootCAs: pool,
	}

	conn, err := tls.Dial("tcp", "127.0.0.1:9443", &config)
	if err != nil {
		// Got error if server presents a bad certificate (server_cert2).
		// x509: certificate signed by unknown authority (possibly because of "crypto/rsa: verification
		// error" while trying to verify candidate authority certificate "serial:1653")
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
