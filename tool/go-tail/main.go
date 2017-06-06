package main

import (
	"fmt"
	"os"

	"github.com/hpcloud/tail"
)

func main() {
	file, err := os.Open("/tmp/buffer")
	if err != nil {
		return
	}
	fmt.Println("file:", file.Name())

	go func() {
		t, _ := tail.TailFile(file.Name(), tail.Config{Follow: true})
		for line := range t.Lines {
			fmt.Println(line.Text)
		}
		fmt.Println("Done")
	}()

	file.Close()

	select {}
}
