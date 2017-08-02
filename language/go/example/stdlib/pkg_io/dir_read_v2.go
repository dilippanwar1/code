package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

var hehe = false

// readSysBlock reads /sys/block and returns a list of devices start with `prefix`.
func readSysBlock(prefix string) ([]string, error) {
	dirs, err := ioutil.ReadDir("/sys/block")
	if err != nil {
		return nil, err
	}

	var result []string
	for _, dir := range dirs {
		if strings.HasPrefix(dir.Name(), prefix) {
			result = append(result, dir.Name())
		}
	}

	if hehe {
		result = append(result, "sdc")
	}

	return result, nil
}

func main() {
	// Before attaching volume, check /sys/block for known disks.
	existing, err := readSysBlock("sd")
	if err != nil {
		return
	}

	hehe = true

	// After attaching volume, check /sys/block again.
	current, err := readSysBlock("sd")
	if err != nil {
		return
	}

	existingMap := make(map[string]bool)
	for _, disk := range existing {
		existingMap[disk] = true
	}

	var diff []string
	for _, disk := range current {
		if _, ok := existingMap[disk]; !ok {
			diff = append(diff, disk)
		}
	}

	if len(diff) != 1 {
		return
	}

	fmt.Println("/dev/" + diff[0])
}
