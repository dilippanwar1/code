package main

import (
	"fmt"
	"syscall"

	"github.com/docker/docker/pkg/mount"
)

func main() {
	FindDirCapacity2("/tmp/looped")
}

func FindDirCapacity2(path string) {
	var s syscall.Statfs_t
	if err := syscall.Statfs(path, &s); err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(s)
	total := uint64(s.Frsize) * s.Blocks
	free := uint64(s.Frsize) * s.Bfree
	avail := uint64(s.Frsize) * s.Bavail
	// inodes = uint64(s.Files)
	// inodesFree = uint64(s.Ffree)
	fmt.Println(float32(total) / 1024.0 / 1024.0 / 1024.0)
	fmt.Println(float32(free) / 1024.0 / 1024.0 / 1024.0)
	fmt.Println(float32(avail) / 1024.0 / 1024.0 / 1024.0)
	return
}

func FindDirCapacity(dir string) (uint64, error) {
	buf := new(syscall.Stat_t)
	err := syscall.Stat(dir, buf)
	major := major(buf.Dev)
	minor := minor(buf.Dev)

	partitions, err := FindAllPartitions()
	if err != nil {
		return 0, err
	}

	for _, partition := range partitions {
		if partition.major == major && partition.minor == minor {
			fmt.Println(partition.available)
			break
		}
	}

	return 0, nil
}

type device struct {
	Device string
	Major  uint
	Minor  uint
}

type partition struct {
	mountpoint string
	major      uint
	minor      uint
	fsType     string
	blockSize  uint
	capacity   uint64
	free       uint64
	available  uint64
}

func major(devNumber uint64) uint {
	return uint((devNumber >> 8) & 0xfff)
}

func minor(devNumber uint64) uint {
	return uint((devNumber & 0xff) | ((devNumber >> 12) & 0xfff00))
}

func getVfsStats(path string) (total uint64, free uint64, avail uint64, inodes uint64, inodesFree uint64, err error) {
	var s syscall.Statfs_t
	if err = syscall.Statfs(path, &s); err != nil {
		return 0, 0, 0, 0, 0, err
	}
	total = uint64(s.Frsize) * s.Blocks
	free = uint64(s.Frsize) * s.Bfree
	avail = uint64(s.Frsize) * s.Bavail
	inodes = uint64(s.Files)
	inodesFree = uint64(s.Ffree)
	return total, free, avail, inodes, inodesFree, nil
}

func FindAllPartitions() (map[string]partition, error) {
	mounts, err := mount.GetMounts()
	if err != nil {
		return nil, err
	}

	partitions := make(map[string]partition, 0)

	for _, mount := range mounts {
		capacity, free, available, _, _, _ := getVfsStats(mount.Mountpoint)
		partitions[mount.Source] = partition{
			fsType:     mount.Fstype,
			mountpoint: mount.Mountpoint,
			major:      uint(mount.Major),
			minor:      uint(mount.Minor),
			capacity:   capacity / 1024 / 1024 / 1024,
			free:       free / 1024 / 1024 / 1024,
			available:  available / 1024 / 1024 / 1024,
		}
	}

	return partitions, nil
}
