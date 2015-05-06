// https://groups.google.com/forum/#!topic/golang-nuts/n_By5xPzDho
//
// The expected pattern for using a sync.Pool, is to set the pool's "New"
// field which is a function returning an interface{}. If you need a new
// object you don't create one, you call Get, and it either returns a pool
// object, or the result of calling new. Then before you use it you should
// assert it to the correct type and then initialize it. When you are done
// with the object you finally put it back in the pool for future use.
// IE, a single goroutine does:
//   1. x := pool.Get() // either returns a pool object, or the result of
//      pool.New
//   2. y := x.(sometype)
//   3. y.Init()
//   4. y.DoStuff()
//   5. pool.Put(y)
package main

import (
	"fmt"
	"sync"
)

type Person struct {
	name string
	age  int
}

func main() {
	var objPool = sync.Pool{
		New: func() interface{} {
			return Person{}
		},
	}

	person := objPool.Get().(Person)
	person.name = "Deyuan"
	fmt.Println(person.name) // Deyuan
	objPool.Put(person)

	another_person := objPool.Get().(Person)
	// This will print 'Deyuan' as well, but note that we can not trust the
	// relation between objects saved and retrieved by Put and Get.
	fmt.Println(another_person.name) // Deyuan
}
