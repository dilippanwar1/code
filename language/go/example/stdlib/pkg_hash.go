package main

import (
	"fmt"
	"hash/fnv"
)

func ihash(s string) uint32 {
	h := fnv.New32a()
	h.Write([]byte(s))
	return h.Sum32()
}

func main() {
	fmt.Println(ihash("abc"))
	fmt.Println(ihash("afaf"))
}
