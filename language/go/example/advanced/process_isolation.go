package main

import (
	"fmt"
	"os"
	"os/exec"
	"syscall"
)

const uid = 1000  // Debian's first non-system user
const gid = 65534 // Debian's nogroup

func main() {
	if len(os.Args) > 1 {
		if os.Args[1] == "run-queue" {
			rc := runQueue(os.Args[2:])
			os.Exit(rc)
			return
		}
	}

	cmd := exec.Command("/proc/self/exe", "run-queue", "blah")
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Credential: &syscall.Credential{
			Uid:    uid,
			Gid:    gid,
			Groups: nil,
		},
	}
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err := cmd.Run()
	if err != nil {
		if os.IsPermission(err) {
			fmt.Println("Operation not permitted. Are you root?")
			os.Exit(2)
		}
		fmt.Printf("%#v\n", err)
		os.Exit(1)
		return
	}
	return
}

func runQueue(args []string) int {
	groups, _ := os.Getgroups()
	fmt.Printf("Running with lowered creds: %d/%d, %v\n",
		os.Getuid(), os.Getgid(), groups)
	return 0
}
