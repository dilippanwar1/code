package main

import "fmt"

func main() {

	// This construct creates a slice.
	p := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(p)

	for i := 0; i < len(p); i++ {
		fmt.Printf("p[%d] = %d\n", i, p[i])
	}

	// This construct creates an empty slice.
	e := []string{}
	fmt.Println("Empty slice:", e)

	// Another way to create a slice is using builtin make. Slice is
	// zero-valued, i.e. "" for string.
	s := make([]string, 3)
	s[0] = "ab"
	s[1] = "cd"
	s[2] = "ef"
	fmt.Println(s)
	fmt.Println(s[0])
	fmt.Println(len(s))

	// Note append returns a new slice.
	t := append(s, "appended")
	fmt.Println("original:", s)
	fmt.Println("appended:", t)

	c := make([]string, len(s))
	copy(c, s)
	fmt.Println("copied:", c)

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

	// Two dimentional slice.  Inner slice needs to be created explicitly,
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
