# TLS example in Go

## About TLS/SSL in general:
- [how-does-ssl-tls-work](http:security.stackexchange.com/questions/20803/how-does-ssl-tls-work])
- [transport-layer-security](https:securityblog.redhat.com/2013/07/24/transport-layer-security/])

## Certificate:
Certificate file usually has extension .crt, .cer or .cert. It's fully
qualified name is "Public Key Certificate".
A public key certificate is a digitally signed document that serves to
validate the sender's authorization and name. The document consists of
a specially formatted block of data that contains the name of the certificate
holder (which may be either a user or a system name) and the holder's
public key, as well as the digital signature of a certification authority
for authentication. The certification authority attests that the sender's
name is the one associated with the public key in the document. If the
signature is valid, and the person examining the certificate trusts the
signer, then they know they can use that key to communicate with its owner.
Public key certificates are part of a public key infrastructure that deals
with digitally signed documents. The other components are public key
encryption, trusted third parties (such as the certification authority),
and mechanisms for certificate publication and issuing.

## PublicKey/PrivateKey:
As mentioned above, certificate contains information about public key.
Private key file ususally has extension .key. A private key is an
encryption/decryption key known only to the party or parties that
exchange secret messages

## PEM:
PEM is Governed by RFCs, it's used preferentially by open-source software.
It can have a variety of extensions (.pem, .key, .cer, .cert, more). It is
a container format that may include just the public key certificate (such as
with Apache installs, and CA certificate files /etc/ssl/certs), or may
include an entire certificate chain including public key, private key, and
root certificates.

## PKI:
A public key infrastructure (PKI) supports the distribution and
identification of public encryption keys, enabling users and computers to
both securely exchange data over networks such as the Internet and verify
the identity of the other party.

## X.509:
X.509 is a widely used standard for a public key infrastructure (PKI)
and Privilege Management Infrastructure (PMI). X.509 specifies, amongst
other things, standard formats for public key certificates, certificate
revocation lists, attribute certificates, and a certification path validation
algorithm.

## Example Steps:
```
$ go run generate.go
$ go run server_tcp.go &
$ go run client_tcp.go
$ go run server_http.go &
$ go run client_http.go
```
