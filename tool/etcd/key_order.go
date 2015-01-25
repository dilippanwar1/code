package main

import (
	"fmt"
	"os"

	"github.com/coreos/go-etcd/etcd"
)

// Return new client if we can connect to etcd; otherwise, return nil and err.
func newEtcdClient() (*etcd.Client, error) {
	client := etcd.NewClient([]string{})
	if _, err := client.Get("/", false, false); err != nil {
		fmt.Println("Unable to connect to ectd.")
		return nil, err
	}
	return client, nil
}

func main() {
	client, err := newEtcdClient()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	// Create three keys.
	client.Set("/key_order/msg1", "{Name:Deyuan,Age:25}", 0)
	client.Set("/key_order/msg3", "{Name:Deyuan,Age:27}", 0)
	client.Set("/key_order/msg2", "{Name:Deyuan,Age:26}", 0)
	// Modify one key.
	client.Set("/key_order/msg2", "{Name:Deyuan,Age:11}", 0)

	// If no sort param is given, the order is last created (observation), by we
	// can not trust it.
	resp, _ := client.Get("/key_order", false, false)
	fmt.Println(resp.Node.Nodes[0])
	fmt.Println(resp.Node.Nodes[1])
	fmt.Println(resp.Node.Nodes[2])

	// If sort param is given, the result is sorted by key.
	resp, _ = client.Get("/key_order", true, false)
	fmt.Println(resp.Node.Nodes[0])
	fmt.Println(resp.Node.Nodes[1])
	fmt.Println(resp.Node.Nodes[2])
}
