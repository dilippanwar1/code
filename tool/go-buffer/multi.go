package main

import (
	"fmt"
	"io/ioutil"

	"github.com/djherbis/buffer"
)

func main() {
	fileObj, err := ioutil.TempFile("/tmp", "buffer")
	if err != nil {
		return
	}
	defer fileObj.Close()

	// Create a 10B mem buffer, 20B file buffer.
	mem := buffer.New(10)
	file := buffer.NewFile(20, fileObj)
	buf := buffer.NewMulti(mem, file)

	// Write 30B (First 10B is in memory, last 20B in file)
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
		fmt.Println("Write 30B:", err)
	}

	fmt.Println("File located at:", fileObj.Name())
}
