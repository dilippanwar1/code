// Iterator pattern is a design pattern in which an iterator is used to traverse
// a container and access the container's elements, without user knowing details
// of the elements.
package main

import "fmt"

// Iterator is an iterface to iterate underline container.
type Iterator interface {
	Reset()

	Next() interface{}
	HasNext() bool
}

type Container interface {
	GetIterator() Iterator
}

// Array backed iterator/container.
type ArrayIterator struct {
	index     int
	container *ArrayContainer
}

type ArrayContainer struct {
	data []interface{}
}

func (ai *ArrayIterator) HasNext() bool {
	return ai.container != nil && ai.index < len(ai.container.data)
}

func (ai *ArrayIterator) Next() interface{} {
	if ai.HasNext() {
		defer func() { ai.index++ }()
		return ai.container.data[ai.index]
	}
	return nil
}

func (ai *ArrayIterator) Reset() {
	ai.index = 0
}

func (ac *ArrayContainer) GetIterator() ArrayIterator {
	return ArrayIterator{index: 0, container: ac}
}

func main() {
	ac := ArrayContainer{data: []interface{}{1, 2, "xyz", 4, 5}}
	iterator := ac.GetIterator()

	for iterator.HasNext() {
		fmt.Println(iterator.Next())
	}

	iterator.Reset()
	fmt.Println(iterator.HasNext())
}
