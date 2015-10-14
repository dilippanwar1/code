package main

import (
	"fmt"
	"os"
	"os/exec"
	"time"
)

func main() {
	// Start a child process asynchronously.
	cmd := exec.Command("./simple.sh")
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err := cmd.Start()
	if err != nil {
		fmt.Printf("Error execing: %v\n", err)
	}
	fmt.Println("Started a process which runs forever ...")

	// NOTE: if no Ctrl+c is pressed, the program will exit after 10s, and child process (simple.sh)
	// will keep running; its parent will be init process. If Ctrl+c is pressed, then parent/child
	// process will both exit. The reason is because of process group, not specific to GO. That is,
	// when receiving SIGINT, OS will send the signal to process group, not just current process, see:
	// http://stackoverflow.com/questions/19243431/why-process-created-by-exec-start-quits-if-its-parent-is-killed-by-sigint
	fmt.Println("Press Ctrl+c to kill me, or wait 10s ...")
	time.Sleep(10 * time.Second)
}
