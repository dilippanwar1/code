package main

import (
	"fmt"
	"time"
)

func main() {
	// The old-fashined approach.
	t := time.Now()
	fmt.Printf("%d-%02d-%02d-%02d-%02d-%02d\n",
		t.Year(), t.Month(), t.Day(),
		t.Hour(), t.Minute(), t.Second())
	// Go introduces a new way to format time. Instead of specifying printf-style
	// placeholders you write your desired format with an actual time.
	fmt.Println(time.Now().Format("2006-01-02-15-04-05"))
}
