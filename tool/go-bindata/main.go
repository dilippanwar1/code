// go-bindata example
//
// Package "go-bindata" is a small utility which generates Go code from any
// file. Useful for embedding binary data in a Go program. `go-bindata` is
// primarily used as a command line tool.
//
// Example:
// First generate bindata: this will generate a file "bindata.go" in current
// working directory (default config).
//  $ go-bindata golden
// Then run the main package:
//  $ go run main.go binddata.go
//
// Internally, it works by reading the files, copy to the new file, with a lot
// of bookkeeping (use fmt.Fprintf), see go-bindata/release.go. The files' data
// are stored as byte array in the result file.
package main

import "fmt"

func main() {
	// Output: [golden/index.html golden/love.c golden/alpha.txt golden/file1.go]
	fmt.Println(AssetNames())

	// Output: [97 98 99 100 101 102 103 10]
	data, _ := Asset("golden/alpha.txt")
	fmt.Println(data)
}
