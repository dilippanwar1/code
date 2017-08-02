package main

import "fmt"

type Reader interface {
	Read(p []byte) (n int, err error)
}

type Writer interface {
	Write(p []byte) (n int, err error)
}

// ReadWriter is the interface that combines the Reader and Writer interfaces.
type ReadWriter interface {
	Reader
	Writer
}

type BufReader struct{}

type BufWriter struct{}

type BufReadWriter struct {
	*BufReader
	*BufWriter
}

func (b *BufReader) Read(p []byte) (n int, err error) {
	fmt.Println("Called Read on BufReader")
	return 0, nil
}

func (b *BufWriter) Write(p []byte) (n int, err error) {
	fmt.Println("Called Write on BufWriter")
	return 0, nil
}

func main() {
	rw := BufReadWriter{&BufReader{}, &BufWriter{}}
	rw.Read(nil)
}
