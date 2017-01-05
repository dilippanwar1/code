// https://blog.golang.org/go-slices-usage-and-internals

package main

import (
	"fmt"
	"io/ioutil"
	"os/exec"
	"regexp"
)

func main() {

	// construction()
	// slicing()
	// sliceFunc()
	// twoDimension()
	// concatenate()
	// misc()
	// sliceAppend()
}

func construction() {
	// This construct creates a slice.
	p := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(p)
	fmt.Println(cap(p)) // 6

	for i := 0; i < len(p); i++ {
		fmt.Printf("p[%d] = %d\n", i, p[i])
	}

	// This construct creates an empty slice.
	e := []string{}
	fmt.Println("Empty slice:", e)
	fmt.Println(cap(e)) // 0

	// Another way to create a slice is using builtin make. Slice is
	// zero-valued, i.e. "" for string.
	s := make([]string, 3)
	s[0] = "ab"
	s[1] = "cd"
	s[2] = "ef"
	fmt.Println(s)
	fmt.Println(s[0])
	fmt.Println(len(s))
}

func slicing() {
	s := []string{"ab", "cd", "ef"}
	// Slice can be sliced; in this case, it's s[2], s[3], s[4].
	s = append(s, "gh", "ij")
	l := s[2:5]
	fmt.Println("sliced", l)

	// This slices up to (but excluding) s[5].
	l = s[:5]
	fmt.Println("sl2:", l)

	// And this slices up from (and including) s[2].
	l = s[2:]
	fmt.Println("sl3:", l)

	// And this slices an entire array.
	l = s[:] // a slice referencing the storage of x
	fmt.Println("sl4:", l)

	// Slicing does not copy the slice's data. It creates a new slice value
	// that points to the original array. This makes slice operations as
	// efficient as manipulating array indices. Therefore, modifying the
	// elements (not the slice itself) of a re-slice modifies the elements
	// of the original slice.
	l[2] = "xy"
	fmt.Println("s is changed:", s)
}

func sliceFunc() {

	sliceChanger := func(s []int) {
		s[0] = 888
	}

	// Passing slice to a function is essentially passing the reference.
	sc := make([]int, 3) // [0 0 0]
	sliceChanger(sc)
	fmt.Println(sc) // [888 0 0]

	cc := []int{1, 2, 3}
	sliceChanger(cc)
	fmt.Println(cc) // [888 2 3]
}

func twoDimension() {
	// Two dimentional slice. Inner slice needs to be created explicitly,
	// and its length can vary.
	twoD := make([][]int, 3)
	for i := 0; i < 3; i++ {
		innerLen := i + 1
		twoD[i] = make([]int, innerLen)
		for j := 0; j < innerLen; j++ {
			twoD[i][j] = i + j
		}
	}
	fmt.Println("2d:", twoD)
}

func concatenate() {
	commandArgs := []string{"-l"}
	commandOtherArgs := []string{"-a"}

	// Concatenate two slices, not the use of "...".
	commandArgs = append(commandArgs, commandOtherArgs...)
	command := exec.Command("ls", commandArgs...)
	output, err := command.CombinedOutput()
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(output))

	// Another way to concatenate.
	args := []string{}
	args = append(args, "source", "target")
	fmt.Println(args) // [source target]
}

func misc() {
	s := []string{"ab", "cd", "ef"}

	// 'append' returns a new slice.
	t := append(s, "appended")
	fmt.Println("original:", s)
	fmt.Println("appended:", t)

	// Copy slice.
	c := make([]string, len(s))
	copy(c, s)
	fmt.Println("copied:", c)

	// We can also 'slice' (verb here) an array, slice.
	ss := [5]int{1, 2, 3, 4, 5}
	fmt.Printf("%T\n", ss[0:2]) // ss[0:2] return a slice
	fmt.Printf("%T\n", ss)

	// We can do len() of nil, the result is 0.
	var ads []string
	fmt.Printf("%v\n", ads == nil) // true
	fmt.Println(len(ads))          // 0
}

func sliceAppend() {
	AppendByte := func(slice []byte, data ...byte) []byte {
		m := len(slice)
		n := m + len(data)
		if n > cap(slice) { // if necessary, reallocate
			// allocate double what's needed, for future growth.
			newSlice := make([]byte, (n+1)*2)
			copy(newSlice, slice)
			slice = newSlice
		}
		slice = slice[0:n]
		copy(slice[m:n], data)
		return slice
	}

	p := []byte{2, 3, 5}
	p = AppendByte(p, 7, 11, 13)
	fmt.Println(p) // p == []byte{2, 3, 5, 7, 11, 13}
}

// As mentioned earlier, re-slicing a slice doesn't make a copy of the underlying
// array. The full array will be kept in memory until it is no longer referenced.
// Occasionally this can cause the program to hold all the data in memory when
// only a small piece of it is needed.
//
// For example, this FindDigits function loads a file into memory and searches
// it for the first group of consecutive numeric digits, returning them as a new
// slice. This code behaves as advertised, but the returned []byte points into
// an array containing the entire file. Since the slice references the original
// array, as long as the slice is kept around the garbage collector can't release
// the array; the few useful bytes of the file keep the entire contents in memory.
// To fix this problem one can copy the interesting data to a new slice before
// returning it.
var digitRegexp = regexp.MustCompile("[0-9]+")

func FindDigits(filename string) []byte {
	b, _ := ioutil.ReadFile(filename)
	return digitRegexp.Find(b)
}

func FindAndCopyDigits(filename string) []byte {
	b, _ := ioutil.ReadFile(filename)
	b = digitRegexp.Find(b)
	c := make([]byte, len(b))
	copy(c, b)
	return c
}
