package main

import (
	"fmt"

	docker "github.com/fsouza/go-dockerclient"
)

func main() {
	endpoint := "unix:///var/run/docker.sock"
	client, _ := docker.NewClient(endpoint)

	images, _ := client.ListImages(true)
	for _, image := range images {
		if false {
			fmt.Println("ID:", image.ID)
			fmt.Println("RepoTags:", image.RepoTags)
			fmt.Println("Created: ", image.Created)
			fmt.Println("Size: ", image.Size)
			fmt.Println("VirtualSize: ", image.VirtualSize)
		}
	}

	// "All" option will list all (running + stopped) containers.
	containers, _ := client.ListContainers(docker.ListContainersOptions{All: true})
	for _, container := range containers {
		fmt.Println("ID:", container.ID)
	}
}
