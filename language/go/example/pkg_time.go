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

	t = time.Minute
	fmt.Println(t)
	fmt.Println(int(t))

	fmt.Println(*periodPtr)

	t1 := time.Date(2012, 1, 1, 0, 0, 0, 0, time.UTC)
	t2 := time.Date(2012, 1, 2, 0, 0, 0, 0, time.UTC)
	fmt.Println(t2.Sub(t1))
}
