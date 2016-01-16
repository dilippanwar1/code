package main

import (
	"fmt"
	"os"
)

func main() {
	fileName := "/tmp/xxxxxx"
	_, err := os.OpenFile(fileName, os.O_APPEND, os.ModePerm)
	if err != nil {
		fmt.Println(err)
	}
}
