package main

import (
	"fmt"
	"time"

	"github.com/samuel/go-zookeeper/zk"
)

func main() {
	c, _, err := zk.Connect([]string{"localhost:2183"}, time.Second)
	if err != nil {
		panic(err)
	}
	children, stat, err := c.Children("/")
	if err != nil {
		panic(err)
	}
	fmt.Printf("Chilren of '/' %+v\n", children)
	fmt.Printf("Stat: %+v\n", stat)

	children, stat, ch, err := c.ChildrenW("/")
	// Same children, stat, but start watching.
	fmt.Println("Start watching...")
	e := <-ch
	fmt.Printf("%+v\n", e)
}
