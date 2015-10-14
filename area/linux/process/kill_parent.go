package main

import (
	"fmt"
	"os"
	"os/exec"
	"time"
)

func main() {
	// Start a child process asynchronously.
	cmd := exec.Command("./evil.sh")
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err := cmd.Start()
	if err != nil {
		fmt.Printf("Error execing: %v\n", err)
	}
	// evil.sh runs command 'kill -9 0', which will send SIGKILL to its process group.
	// Parent process belongs to the process group, so it will exit prematurely.
	time.Sleep(10 * time.Second)
}
