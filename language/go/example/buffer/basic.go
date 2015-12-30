package main

import (
	"fmt"

	"github.com/glycerine/rbuf"
)

func main() {
	buf := rbuf.NewFixedSizeRingBuf(12 * 1024)

	buf.Write([]byte("ABCDEFG\n"))
	buf.Write([]byte("AAAAAAA\n"))
	buf.Write([]byte("CCCCCCC\n"))

	// reader1 := bufio.NewReader(buf)
	// line1, _ := reader1.ReadString('\n')
	// fmt.Printf(line1)

	// reader2 := bufio.NewReader(buf)
	// line2, _ := reader1.ReadString('\n')
	// fmt.Printf(line2)

	xx := make([]byte, 10)
	buf.Read(xx)
	fmt.Println(string(xx))

	buf.Read(xx)
	fmt.Println(string(xx))
}
