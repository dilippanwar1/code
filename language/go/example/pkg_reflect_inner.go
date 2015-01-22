package main

import (
	"fmt"
	"reflect"
)

type Node struct {
	Spec   NodeSpec
	Status NodeStatus
}

type NodeSpec struct {
	CPU    int
	Memory int
}

type NodeStatus struct {
	HostIP    string
	Condition NodeCondition
}

type NodeCondition struct {
	Healthy bool
}

func main() {
	node := Node{
		Spec: NodeSpec{
			CPU:    100,
			Memory: 1024,
		},
		Status: NodeStatus{
			HostIP: "127.0.0.1",
			Condition: NodeCondition{
				Healthy: true,
			},
		},
	}

	fmt.Println(node)
	fmt.Println(reflect.TypeOf(node))               // main.Node
	fmt.Println(reflect.TypeOf(node.Spec))          // main.NodeSpec
	fmt.Println(reflect.TypeOf(node.Status.HostIP)) // string
}
