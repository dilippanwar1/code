package main

import (
	_ "crypto/sha256"
	_ "crypto/sha512"
	"fmt"
	"io"
	"strings"

	digest "github.com/opencontainers/go-digest"
)

func main() {
	// Create a digest and get its verifier; verifier implements io.Write.
	id := digest.FromBytes([]byte("my content"))
	verifier := id.Verifier()

	io.Copy(verifier, strings.NewReader("my content !!"))
	fmt.Println(verifier.Verified()) // false
}
