package main

import (
	"fmt"
	"net"
)

func main() {
	intfs, err := net.Interfaces()
	if err != nil {
		fmt.Println("Error list interfaces:", err)
		return
	}
	i := 0
	for i = range intfs {
		if flagsSet(intfs[i].Flags, net.FlagUp) && flagsClear(intfs[i].Flags, net.FlagLoopback|net.FlagPointToPoint) {
			// This interface should suffice.
			break
		}
	}
	if i == len(intfs) {
		fmt.Println("No one fits")
		return
	}
	fmt.Println("Found interface of index:", i)
	addrs, err := intfs[i].Addrs()
	fmt.Printf("%+v\n", intfs[i])
	fmt.Println(addrs)
}

func flagsSet(flags net.Flags, test net.Flags) bool {
	return flags&test != 0
}

func flagsClear(flags net.Flags, test net.Flags) bool {
	return flags&test == 0
}
