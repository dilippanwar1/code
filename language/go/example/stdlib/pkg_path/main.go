package main

import (
	"fmt"
	"path"
	"path/filepath"
)

func main() {
	name := "/tmp"
	fmt.Println(path.Dir(name))
	fmt.Println(path.Base(name))

	name = "/"
	fmt.Println(path.Dir(name))  // output: "/"
	fmt.Println(path.Base(name)) // output: "/"

	name = "/etc/"
	fmt.Println(path.Clean(name)) // output: "/"

	name = "/var/lib/kubelet/pods/b9a14925-320d-11e7-b142-8825937fa049/volumes/kubernetes.io~local-volume/local-pv"
	fmt.Println(filepath.Split(name))

	paths := []string{
		"/a/b/c",
		"/b/c",
		"./b/c",
	}
	base := "/a"

	fmt.Println("Join(basepath, Rel(basepath, targpath)) is equivalent to targpath itself.")
	for _, p := range paths {
		rel, err := filepath.Rel(base, p)
		fmt.Printf("base: %q target: %q\t --> result: %v\terror: err%v\n", base, p, rel, err)
	}
}
