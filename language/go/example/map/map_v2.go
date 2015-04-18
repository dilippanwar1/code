package main

import "fmt"

type NodeAddressType string

// These are valid address types of node.
const (
	NodeExternalIP NodeAddressType = "ExternalIP"
	NodeInternalIP NodeAddressType = "InternalIP"
)

type NodeAddress struct {
	Type    NodeAddressType `json:"type"`
	Address string          `json:"address"`
}

func main() {
	address1 := NodeAddress{Type: NodeExternalIP, Address: "1.1.1.1"}
	address2 := NodeAddress{Type: NodeExternalIP, Address: "1.1.1.1"}

	addresses := make(map[NodeAddress]bool)
	addresses[address1] = true
	// output will be "Exist!". In Go, map keys may be of any type that is
	// comparable. The language spec defines this precisely, but in short,
	// comparable types are boolean, numeric, string, pointer, channel, and
	// interface types, and structs or arrays that contain only those types.
	if _, ok := addresses[address2]; ok {
		fmt.Println("Exist!")
	} else {
		fmt.Println("Not exist!")
	}
}
