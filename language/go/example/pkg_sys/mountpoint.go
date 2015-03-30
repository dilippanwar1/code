package main

import (
	"fmt"
	"os"
	"syscall"
)

// Determine if a directory is a mountpoint, by comparing the device for the directory
// with the device for it's parent.  If they are the same, it's not a mountpoint, if they're
// different, it is.
func IsMountPoint(file string) (bool, error) {
	stat, err := os.Stat(file)
	if err != nil {
		fmt.Println("Error from os.Stat")
		return false, err
	}
	rootStat, err := os.Lstat(file + "/..")
	fmt.Println("Error from os.Lstat")
	if err != nil {
		return false, err
	}
	// If the directory has the same device as parent, then it's not a mountpoint.
	return stat.Sys().(*syscall.Stat_t).Dev != rootStat.Sys().(*syscall.Stat_t).Dev, nil
}

func main() {
	file := "/media/deyuan/System"
	is_mountpoint, err := IsMountPoint(file)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(is_mountpoint)
}
