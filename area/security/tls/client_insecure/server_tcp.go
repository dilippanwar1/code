// Server presents a self-signed signed certificate, which is not trusted by client.
package main

import (
	"crypto/tls"
	"crypto/x509"
	"io/ioutil"
	"log"
	"net"
)

func main() {
	cert_b, _ := ioutil.ReadFile("../certs.d/server_cert2.crt")
	priv_b, _ := ioutil.ReadFile("../certs.d/server_cert2.key")
	priv, _ := x509.ParsePKCS1PrivateKey(priv_b)

	config := tls.Config{
		// Certificates is the certificate of the server, used to present to the other side of
		// the connection (the client). This is required for tls communication. Here since the
		// certificate is self-signed, we have only one certificate. In practical world, this
		// may contain a handful of certificate: certificate chain.
		Certificates: []tls.Certificate{
			tls.Certificate{
				Certificate: [][]byte{cert_b},
				PrivateKey:  priv,
			},
		},
	}

	service := "0.0.0.0:9443"
	listener, err := tls.Listen("tcp", service, &config)
	if err != nil {
		log.Fatalf("server: listen: %s", err)
	}
	log.Print("server: listening: ", service)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("server: accept: %s", err)
			break
		}
		defer conn.Close()
		log.Printf("server: accepted from %s", conn.RemoteAddr())
		go handleClient(conn)
	}
}

func handleClient(conn net.Conn) {
	defer conn.Close()
	buf := make([]byte, 512)
	for {
		log.Print("server: conn: waiting")
		n, err := conn.Read(buf)
		if err != nil {
			if err != nil {
				log.Printf("server: conn: read: %s", err)
			}
			break
		}

		log.Printf("server: conn: echo %q\n", string(buf[:n]))
		n, err = conn.Write(buf[:n])
		if err != nil {
			log.Printf("server: write: %s", err)
			break
		}
	}
	log.Println("server: conn: closed")
}
