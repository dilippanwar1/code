package main

import (
	"flag"
	"fmt"
	"time"
)

func main() {
	// Input will be 10s, 1m, 2h, etc, e.g.
	// $ go run time.go --period=50s
	periodPtr := flag.Duration("period", 10*time.Second, "The period flag.")
	flag.Parse()

	t := time.Second
	fmt.Println(t)      // 1s
	fmt.Println(int(t)) // 1000000000 (ns)

	t = time.Minute
	fmt.Println(t)      // 1m0s
	fmt.Println(int(t)) // 60000000000 (ns)

	fmt.Println(*periodPtr) // 50s

	t1 := time.Date(2012, 1, 1, 0, 0, 0, 0, time.UTC)
	t2 := time.Date(2012, 1, 2, 0, 0, 0, 0, time.UTC)
	fmt.Println(t2.Sub(t1)) // 24h0m0s
}
