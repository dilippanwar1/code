package main

import (
	"fmt"

	"github.com/coreos/go-etcd/etcd"
)

func main() {
	client := etcd.NewClient([]string{})

	// Create three keys.
	client.Set("/key_order/msg1", "{Name:Deyuan,Age:25}", 0)
	client.Set("/key_order/msg3", "{Name:Deyuan,Age:27}", 0)
	client.Set("/key_order/msg4/gsm2", "{Name:Deyuan,Age:22}", 0)
	client.Set("/key_order/msg2", "{Name:Deyuan,Age:26}", 0)
	client.Set("/key_order/msg4/gsm1", "{Name:Deyuan,Age:21}", 0)
	// Modify one key.
	client.Set("/key_order/msg2", "{Name:Deyuan,Age:11}", 0)

	// If no sort param is given, the order is last created (observation), by we
	// can not trust it.
	resp, _ := client.Get("/key_order", false, true)
	fmt.Println("------------------- unsorted --------------------")
	fmt.Println(resp.Node.Nodes[0])
	fmt.Println(resp.Node.Nodes[1])
	fmt.Println(resp.Node.Nodes[2])
	fmt.Println(resp.Node.Nodes[3])

	// If sort param is given, the result is sorted by key.
	fmt.Println("------------------- sorted --------------------")
	resp, _ = client.Get("/key_order", true, true)
	fmt.Println(resp.Node.Nodes[0])
	fmt.Println(resp.Node.Nodes[1])
	fmt.Println(resp.Node.Nodes[2])
	fmt.Println(resp.Node.Nodes[3])
}
