package main

import (
	"fmt"
	"sort"
	"time"
)

type Node struct {
	Key           string     `json:"key, omitempty"`
	Value         string     `json:"value,omitempty"`
	Dir           bool       `json:"dir,omitempty"`
	Expiration    *time.Time `json:"expiration,omitempty"`
	TTL           int64      `json:"ttl,omitempty"`
	Nodes         Nodes      `json:"nodes,omitempty"`
	ModifiedIndex uint64     `json:"modifiedIndex,omitempty"`
	CreatedIndex  uint64     `json:"createdIndex,omitempty"`
}

type Nodes []*Node

// interfaces for sorting
func (ns Nodes) Len() int {
	return len(ns)
}

func (ns Nodes) Less(i, j int) bool {
	fmt.Println(ns[i].Key)
	return ns[i].Key < ns[j].Key
}

func (ns Nodes) Swap(i, j int) {
	ns[i], ns[j] = ns[j], ns[i]
}

func main() {
	node := Node{
		Nodes: Nodes{
			{
				Value: `{"name": "directory1"}`,
				Dir:   true,
				Nodes: Nodes{
					{
						Value:         `{"id":"foo","kind":"Pod","apiVersion":"v1beta1"}`,
						ModifiedIndex: 1,
					},
				},
			},
			{
				Value: `{"name": "directory3"}`,
				Dir:   true,
				Nodes: Nodes{
					{
						Value:         `{"id":"bar","kind":"Pod","apiVersion":"v1beta1"}`,
						ModifiedIndex: 2,
					},
				},
			},
			{
				Value: `{"name": "directory2"}`,
				Dir:   true,
				Nodes: Nodes{
					{
						Value:         `{"id":"bar","kind":"Pod","apiVersion":"v1beta1"}`,
						ModifiedIndex: 2,
					},
				},
			},
		},
	}

	sort.Sort(node.Nodes)
	fmt.Println(node.Nodes[0])
	fmt.Println(node.Nodes[1])
	fmt.Println(node.Nodes[2])
}
