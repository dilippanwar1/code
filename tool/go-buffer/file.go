package main

import (
	"fmt"
	"io/ioutil"

	"github.com/djherbis/buffer"
)

func main() {
	file, err := ioutil.TempFile("/tmp", "buffer")
	if err != nil {
		return
	}
	defer file.Close()

	// Create a 20B file buffer. Based on the implementation, data is
	// actually written to file directly without buffering.
	buf := buffer.NewFile(20, file)

	// Write 30B
	_, err = buf.Write([]byte("AAAAAAAAA\n"))
	if err != nil {
		fmt.Println("Write 10B:", err)
	}
	_, err = buf.Write([]byte("BBBBBBBBB\n"))
	if err != nil {
		fmt.Println("Write 20B:", err)
	}
	_, err = buf.Write([]byte("CCCCCCCCC\n"))
	if err != nil {
		// Error writing the last 10 Bytes as we only support 20B.
		fmt.Println("Write 30B:", err)
	}

	fmt.Println("File located at:", file.Name())
}
