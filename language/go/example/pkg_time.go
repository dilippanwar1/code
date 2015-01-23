package main

import (
	"flag"
	"fmt"
	"time"
)

func main() {

	periodPtr := flag.Duration("period", 10*time.Second, "The period flag.")

	flag.Parse()

	t := time.Second
	fmt.Println(t)
	fmt.Println(int(t))

	fmt.Println(*periodPtr)
}
