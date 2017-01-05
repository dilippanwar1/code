// hashring is a consistent hashing that can be used when the number of server
// nodes can increase or decrease (like in memcached). The hashing ring is
// built using the same algorithm as libketama.
//   https://github.com/RJ/ketama
package main

import (
	"fmt"

	"github.com/serialx/hashring"
)

func main() {
	memcacheServers := []string{
		"192.168.0.246:11212",
		"192.168.0.247:11212",
		"192.168.0.249:11212",
	}

	// Calculate the node where 'my_key' landed.
	ring := hashring.New(memcacheServers)
	server, _ := ring.GetNode("my_key")
	fmt.Println(server)

	// Add/Remove node and recalculate.
	ring = ring.RemoveNode("192.168.0.246:11212")
	ring = ring.AddNode("192.168.0.250:11212")
	server, _ = ring.GetNode("my_key")
	fmt.Println(server)

	// Node weights are supported.
	weights := make(map[string]int)
	weights["192.168.0.246:11212"] = 1
	weights["192.168.0.247:11212"] = 2
	weights["192.168.0.249:11212"] = 1

	ring = hashring.NewWithWeights(weights)
	server, _ = ring.GetNode("my_key")
	fmt.Println(server)
}
