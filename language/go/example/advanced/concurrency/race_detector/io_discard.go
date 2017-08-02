package main

import (
	"crypto/sha1"
	"fmt"
	"hash"
	"io"
	"io/ioutil"
	"os"
)

type trackDigestReader struct {
	r io.Reader
	h hash.Hash
}

func (t trackDigestReader) Read(p []byte) (int, error) {
	n, err := t.r.Read(p)
	t.h.Write(p[:n])
	return n, err
}

func main() {
	buffer := make([]byte, 16*1024)
	file, err := os.Open("/home/deyuan/.bashrc")
	if err != nil {
		fmt.Println(err)
		return
	}
	tdr := trackDigestReader{file, sha1.New()}
	n, err := tdr.Read(buffer)
	fmt.Println(n)
	fmt.Println(string(buffer))
	fmt.Println(err)
	fmt.Printf("%x\n", tdr.h.Sum(nil))

	file, err = os.Open("/home/deyuan/.bashrc")
	tdr = trackDigestReader{file, sha1.New()}
	io.Copy(ioutil.Discard, tdr)
	fmt.Printf("%x\n", tdr.h.Sum(nil))
}
