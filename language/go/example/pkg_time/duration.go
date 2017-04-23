package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println(time.Duration(int64(-1)))
	fmt.Println(time.Duration(int64(-1)) < 0)
}
