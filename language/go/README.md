## Experiment with Go

Run `source ./build.sh` to override GOPATH. The directory also contains Go related tools, e.g.
to experiment with docker-client:

```sh
$ source ./build.sh
$ go get github.com/fsouza/go-dockerclient
$ go run src/github.com/ddysher/docker/client.go
```
