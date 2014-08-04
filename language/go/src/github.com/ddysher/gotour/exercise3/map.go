// Implement WordCount. It should return a map of the counts of
// each “word” in the string s.

package main

import (
	"strings"
	"code.google.com/p/go-tour/wc"
)

func WordCount(s string) map[string]int {
	words := strings.Fields(s)
	// Use 'make' to create a map.
	count := make(map[string]int)
	// Use 'range' to iterate map (and slice).
	for _, word := range words {
		// If key not in map, default is 0 for int.
		count[word]++
	}
	return count
}

func main() {
	wc.Test(WordCount)
}
