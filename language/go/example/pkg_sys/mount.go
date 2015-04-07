package main

import (
	"fmt"
	"syscall"
)

func main() {
	// if err := syscall.Mount("172.17.0.35:/lib", "/tmp/lib", "nfs", uintptr(0), ""); err != nil {
	// 	fmt.Println(err)
	// }
	// To mount NFS, we need to supply "addr=%s" as data option.
	if err := syscall.Mount("172.17.0.35:/lib", "/tmp/lib", "nfs", uintptr(0), "addr=172.17.0.35"); err != nil {
		fmt.Println(err)
	}
}
