package main

import (
	"encoding/json"
	"fmt"
	"reflect"

	"github.com/mitchellh/mapstructure"
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
	var jsonObj map[string]interface{}
	jsonString := []byte(`{"CPU": 10, "Memory": 2048}`)
	json.Unmarshal(jsonString, &jsonObj)

	var result NodeSpec
	err := mapstructure.Decode(jsonObj, &result)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(result)
	fmt.Println(reflect.TypeOf(result))
}
