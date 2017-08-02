package main

import (
	"container/list"
	"fmt"
	"runtime"
)

func main() {
	// doubleRemovePanic()
	pushBackChangedList()
}

func doubleRemovePanic() {
	l := list.New()
	l.PushBack(1)
	fmt.Println(l.Front().Value) // 1

	// Remove the single element from list.
	value := l.Remove(l.Front())
	fmt.Println(value) // 1

	// Another remove will result in panic. Tested on golang 1.5.3.
	value1 := l.Remove(l.Front()) // panic: runtime error: invalid memory address or nil pointer dereference
	fmt.Println(value1)
}

func pushBackChangedList() {
	runtime.GOMAXPROCS(8)
	l := list.New()
	ls := list.New()
	for i := 0; i < 10000; i++ {
		ls.PushBack(i)
	}
	// PushBackList loops through ls by reading its length first; if length changes
	// concurrently, then it will loop wrong number of elements.
	go ls.Remove(l.Back())
	l.PushBackList(ls) //invalid memory address or nil pointer dereference
}
