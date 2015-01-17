// generate.go generates two certificates and private keys.
package main

import (
	"bytes"
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"crypto/x509/pkix"
	"encoding/pem"
	"io/ioutil"
	"log"
	"math/big"
	"os"
	"time"
)

func main() {
	// 'serverCert' is self-signed; 'clientCert' is signed by serverCert.
	serverCert, _ := CreateSelfSignedCertificateAndKey("CMU", "ca1.crt", "ca1.key")
	clientCert, _ := CreateCertificateAndKey("UESTC", "cert2.crt", "cert2.key", "ca1.crt", "ca1.key")
	if err := EncodeToPEMFormat("ca1.crt", "ca1.key"); err != nil {
		log.Print("Err encoding to PEM format", err)
	}

	err1 := serverCert.CheckSignatureFrom(serverCert)
	log.Print("Check signature:", err1 == nil)
	err2 := clientCert.CheckSignatureFrom(serverCert)
	log.Print("Check signature:", err2 == nil)
}

// CreateSelfSignedCertificateAndKey creates self-signed certificate and key, and save them to given files.
func CreateSelfSignedCertificateAndKey(organization, certPath, keyPath string) (*x509.Certificate, error) {
	// Create a x509 certificate template.
	template := x509.Certificate{
		SerialNumber: big.NewInt(1653),
		Subject: pkix.Name{
			Country:      []string{"China"},
			Organization: []string{organization},
		},
		NotBefore:             time.Now(),
		NotAfter:              time.Now().AddDate(10, 0, 0),
		SubjectKeyId:          []byte{1, 2, 3, 4, 5},
		BasicConstraintsValid: true,
		IsCA:        true,
		ExtKeyUsage: []x509.ExtKeyUsage{x509.ExtKeyUsageClientAuth, x509.ExtKeyUsageServerAuth},
		KeyUsage:    x509.KeyUsageDigitalSignature | x509.KeyUsageCertSign,
	}

	// Generate a RSA key pair (public & private key).
	priv, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return nil, err
	}
	pub := &priv.PublicKey

	// Generate certificate. Note we are using the same template for parent, which means
	// the created certificate will be self-signed.
	cerBytes, err := x509.CreateCertificate(rand.Reader, &template, &template, pub, priv)
	if err != nil {
		log.Print("Error creating certificate")
		return nil, err
	}

	writeCertificateAndKey(certPath, keyPath, cerBytes, x509.MarshalPKCS1PrivateKey(priv))

	return x509.ParseCertificate(cerBytes)
}

// CreateCertificateAndKey creates certificate and key, and save them to given files.
// It also takes a parent certificate to sign.
func CreateCertificateAndKey(organization, certPath, keyPath, parentCertPath, parentKeyPath string) (*x509.Certificate, error) {
	// Create a x509 certificate template.
	template := x509.Certificate{
		SerialNumber: big.NewInt(1658),
		Subject: pkix.Name{
			Country:      []string{"China"},
			Organization: []string{organization},
		},
		NotBefore:    time.Now(),
		NotAfter:     time.Now().AddDate(10, 0, 0),
		SubjectKeyId: []byte{1, 2, 3, 4, 6},
		ExtKeyUsage:  []x509.ExtKeyUsage{x509.ExtKeyUsageClientAuth, x509.ExtKeyUsageServerAuth},
		KeyUsage:     x509.KeyUsageDigitalSignature | x509.KeyUsageCertSign,
	}

	// Load parent certificate and private key to sign.
	parentCertBytes, _ := ioutil.ReadFile(parentCertPath)
	parentKeyBytes, _ := ioutil.ReadFile(parentKeyPath)
	parentCert, _ := x509.ParseCertificate(parentCertBytes)
	parentKey, _ := x509.ParsePKCS1PrivateKey(parentKeyBytes)

	// Generate a RSA key pair (public & private key).
	priv, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return nil, err
	}
	pub := &priv.PublicKey

	cerBytes, _ := x509.CreateCertificate(rand.Reader, &template, parentCert, pub, parentKey)
	if err != nil {
		log.Print("Error creating certificate")
		return nil, err
	}

	writeCertificateAndKey(certPath, keyPath, cerBytes, x509.MarshalPKCS1PrivateKey(priv))

	return x509.ParseCertificate(cerBytes)
}

// EncodeToPEMForm takes paths to certificate and key, read them, and encode into PEM format respectively.
// PEM files are saved by appending '.pem' extension.
func EncodeToPEMFormat(certPath, keyPath string) error {
	certBytes, err := ioutil.ReadFile(certPath)
	if err != nil {
		return err
	}
	keyBytes, err := ioutil.ReadFile(keyPath)
	if err != nil {
		return err
	}

	// Generate cert
	certBuffer := bytes.Buffer{}
	if err := pem.Encode(&certBuffer, &pem.Block{Type: "CERTIFICATE", Bytes: certBytes}); err != nil {
		return err
	}

	// Generate key
	keyBuffer := bytes.Buffer{}
	if err := pem.Encode(&keyBuffer, &pem.Block{Type: "RSA PRIVATE KEY", Bytes: keyBytes}); err != nil {
		return err
	}

	return writeCertificateAndKey(certPath+".pem", keyPath+".pem", certBuffer.Bytes(), keyBuffer.Bytes())
}

// Write to files. Optionally, we can also encode to PEM format:
//   certBuffer := bytes.Buffer{}
//   keyBuffer := bytes.Buffer{}
//   pem.Encode(&certBuffer, &pem.Block{Type: "CERTIFICATE", Bytes: cerBytes})
//   pem.Encode(&keyBuffer, &pem.Block{Type: "RSA PRIVATE KEY", Bytes: x509.MarshalPKCS1PrivateKey(priv)})
//   ioutil.WriteFile(certPath, certBuffer.Bytes(), os.FileMode(0644))
//   ioutil.WriteFile(keyPath, keyBuffer.Bytes(), os.FileMode(0600)
func writeCertificateAndKey(certPath, keyPath string, cerBytes, keyBytes []byte) error {
	log.Print("Write certificate to:", certPath)
	log.Print("Write key to:", keyPath)
	if err := ioutil.WriteFile(certPath, cerBytes, os.FileMode(0777)); err != nil {
		return err
	}
	if err := ioutil.WriteFile(keyPath, keyBytes, os.FileMode(0777)); err != nil {
		return err
	}
	return nil
}
