package main

import (
	"fmt"
	"os"
	"os/exec"
	"syscall"
)

func main() {
	// cmd1 will run without problem, but we haven't set its stdin/stdout, so we can't
	// see its output yet. According to go documentation, if stdin/stdout are not set,
	// the new process will read from/write to os.DevNull.
	cmd1 := exec.Command("/bin/echo", "Hello world from command1")
	if err := cmd1.Run(); err != nil {
		fmt.Printf("Error running command1 %v\n", err)
	}

	// Set cmd2's stdout to os.Stdout, so we'll be able to see the output.
	cmd2 := exec.Command("/bin/echo", "Hello world from command2")
	cmd2.Stdout = os.Stdout
	if err := cmd2.Run(); err != nil {
		fmt.Printf("Error running command2 %v\n", err)
	}

	// cmd3 will exit with status 1, since we haven't set its stdin yet.
	cmd3 := exec.Command("/bin/bash", "./simple.sh")
	if err := cmd3.Run(); err != nil {
		fmt.Printf("Error running command3 %v\n", err)
		if exiterr, ok := err.(*exec.ExitError); ok {
			fmt.Println("Status code:", exiterr.Sys().(syscall.WaitStatus).ExitStatus())
		}
	}

	// Set cmd4's stdin to os.Stdin, it will run successfully.
	cmd4 := exec.Command("/bin/bash", "./simple.sh")
	cmd4.Stdin = os.Stdin
	if err := cmd4.Run(); err != nil {
		fmt.Printf("Error running command4 %v\n", err)
	}
}
