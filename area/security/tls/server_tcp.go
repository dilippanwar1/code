package main

import (
	"crypto/tls"
	"crypto/x509"
	"io/ioutil"
	"log"
	"net"
)

func main() {
	ca_b, _ := ioutil.ReadFile("ca1.crt")
	ca, _ := x509.ParseCertificate(ca_b)
	priv_b, _ := ioutil.ReadFile("ca1.key")
	priv, _ := x509.ParsePKCS1PrivateKey(priv_b)

	pool := x509.NewCertPool()
	pool.AddCert(ca)

	// TLS Server Configuration.
	config := tls.Config{
		// Certificates is the certificate of the server, used to present to the other side of
		// the connection (the client). This is required for tls communication. Here since the
		// certificate is self-signed, we have only one certificate. In practical world, this
		// may contain a handful of certificate: certificate chain.
		Certificates: []tls.Certificate{
			tls.Certificate{
				Certificate: [][]byte{ca_b},
				PrivateKey:  priv,
			},
		},
		// Server can optionally require client to provide certificate (here using ClientAuth).
		// If it does, ClientCAs hold all root certificate authorities server trust, and use
		// them to verify clients. In our example, server trusts 'ca', which is self-signed by
		// server, since in generate.go, client's certificate is signed by server, thus client
		// can talk to this serve.
		ClientAuth: tls.RequireAndVerifyClientCert,
		ClientCAs:  pool,
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

		// Get basic TLS details about the established connection.
		tlscon, ok := conn.(*tls.Conn)
		if ok {
			state := tlscon.ConnectionState()
			sub := state.PeerCertificates[0].Subject
			log.Println(sub)
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
