package main

import (
	"fmt"
	"syscall"

	"golang.org/x/sys/unix"
)

// FSInfo linux returns (available bytes, byte capacity, byte usage, total inodes, inodes free, inode usage, error)
// for the filesystem that path resides upon.
func FsInfo(path string) (int64, int64, int64, int64, int64, int64, error) {
	statfs := &syscall.Statfs_t{}
	err := syscall.Statfs(path, statfs)
	if err != nil {
		return 0, 0, 0, 0, 0, 0, err
	}

	// Available is blocks available * fragment size
	available := int64(statfs.Bavail) * int64(statfs.Bsize)

	// Capacity is total block count * fragment size
	capacity := int64(statfs.Blocks) * int64(statfs.Bsize)

	// Usage is block being used * fragment size (aka block size).
	usage := (int64(statfs.Blocks) - int64(statfs.Bfree)) * int64(statfs.Bsize)

	inodes := int64(statfs.Files)
	inodesFree := int64(statfs.Ffree)
	inodesUsed := inodes - inodesFree

	return available, capacity, usage, inodes, inodesFree, inodesUsed, nil
}

func GetFsAvailableByte(fullPath string) (uint64, error) {
	var s unix.Statfs_t
	if err := unix.Statfs(fullPath, &s); err != nil {
		return 0, err
	}
	return uint64(s.Frsize) * (s.Blocks - s.Bfree + s.Bavail), nil
}

func main() {
	fmt.Println(FsInfo("/home"))
	fmt.Println(GetFsAvailableByte("/home"))
}
