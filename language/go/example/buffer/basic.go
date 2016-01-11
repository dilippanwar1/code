package main

import (
	"fmt"
	"io/ioutil"
	"time"

	"github.com/djherbis/buffer"
	"github.com/hpcloud/tail"
)

func main() {
	// Create a File-based Buffer with max size 100MB
	file, err := ioutil.TempFile("", "buffer")
	if err != nil {
		return
	}
	// defer os.Remove(file.Name())
	defer file.Close()
	buf := buffer.NewFile(100*1024*1024, file)

	count := 0
	go func() {
		ticker := time.NewTicker(time.Second)
		for {
			<-ticker.C
			buf.Write([]byte(fmt.Sprintf("%d\n", count)))
			count++
		}
	}()

	go func() {
		t, _ := tail.TailFile(file.Name(), tail.Config{Follow: true})
		for line := range t.Lines {
			fmt.Println("1", line.Text)
		}
	}()

	go func() {
		t, _ := tail.TailFile(file.Name(), tail.Config{Follow: true})
		for line := range t.Lines {
			fmt.Println("2", line.Text)
		}
	}()

	select {}
	// xx := make([]byte, 10)
	// buf.Read(xx)
	// fmt.Printf(string(xx))

	// buf.Reset()

	// buf.Read(xx)
	// fmt.Printf(string(xx))
}
