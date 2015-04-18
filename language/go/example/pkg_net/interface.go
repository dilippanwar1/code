package main

import (
	"fmt"
	"net"
)

func main() {
	// Interfaces returns a list of the system's network interfaces.
	intfs, err := net.Interfaces()
	if err != nil {
		fmt.Println("Error list interfaces:", err)
		return
	}

	// There are a couple of flags to test the properties of interfaces.
	i := 0
	for i = range intfs {
		if isFlagsSet(intfs[i].Flags, net.FlagUp) && isFlagsClear(intfs[i].Flags, net.FlagLoopback|net.FlagPointToPoint) {
			// Find an interface that's up but not a loopback.
			break
		}
	}
	if i == len(intfs) {
		fmt.Println("No one fits")
		return
	}

	fmt.Printf("Found interface from index[%d], %+v\n", i, intfs[i])
	addrs, err := intfs[i].Addrs()
	fmt.Println(addrs)
}

func isFlagsSet(flags net.Flags, test net.Flags) bool {
	return flags&test != 0
}

func isFlagsClear(flags net.Flags, test net.Flags) bool {
	return flags&test == 0
}
