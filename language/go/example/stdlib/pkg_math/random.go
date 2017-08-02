package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	letterBytes   = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	letterIdxBits = 6                    // 6 bits to represent a letter index
	letterIdxMask = 1<<letterIdxBits - 1 // All 1-bits, as many as letterIdxBits
	letterIdxMax  = 63 / letterIdxBits   // # of letter indices fitting in 63 bits
)

var src = rand.NewSource(time.Now().UnixNano())

func main() {
	fmt.Println(RandStringBytesMaskImprSrc(16))
	fmt.Println(RandomRange(3, 20))
	fmt.Println(ShuffleString("Caicloud"))
	fmt.Println("Caicloud")
	fmt.Println(ShuffleStringWithIndex("Caicloud"))
}

func RandStringBytesMaskImprSrc(n int) string {
	b := make([]byte, n)
	// A src.Int63() generates 63 random bits, enough for letterIdxMax characters!
	for i, cache, remain := n-1, src.Int63(), letterIdxMax; i >= 0; {
		if remain == 0 {
			cache, remain = src.Int63(), letterIdxMax
		}
		if idx := int(cache & letterIdxMask); idx < len(letterBytes) {
			b[i] = letterBytes[idx]
			i--
		}
		cache >>= letterIdxBits
		remain--
	}

	return string(b)
}

func RandomRange(min, max int) int {
	rand.Seed(time.Now().UnixNano())
	return rand.Intn(max-min) + min
}

func ShuffleString(str string) string {
	slice := []rune(str) // Use rune so we can shuffle uft8 chars.
	for i := range slice {
		j := rand.Intn(i + 1)
		slice[i], slice[j] = slice[j], slice[i]
	}
	return string(slice)
}

// ShuffleStringWithIndex returns the shuffled string, and original index.
func ShuffleStringWithIndex(str string) (string, []int) {
	slice := []rune(str) // Use rune so we can shuffle uft8 chars.
	var index []int
	for i := 0; i < len(slice); i++ {
		index = append(index, i)
	}
	for i := range slice {
		j := rand.Intn(i + 1)
		index[i], index[j] = index[j], index[i]
		slice[i], slice[j] = slice[j], slice[i]
	}
	return string(slice), index
}
