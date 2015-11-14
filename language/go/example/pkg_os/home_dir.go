package main

import (
	"fmt"
	"log"
	"os/user"
)

// GetHomeDir gets current user's home directory.
func GetHomeDir() string {
	usr, err := user.Current()
	if err != nil {
		log.Fatal(err)
	}
	return usr.HomeDir
}

func main() {
	fmt.Println(GetHomeDir())
}
