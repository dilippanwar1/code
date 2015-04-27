// Run a local NFS server to experiment:
//   $ docker run --name nfs --privileged cpuguy83/nfs-server /lib
// Then get the ipaddress of the container:
//   $ docker inspect -f '{{ .NetworkSettings.IPAddress }}' <container-id>
package main

import (
	"os/exec"
	"strings"

	"github.com/golang/glog"
)

func main() {
	// if err := syscall.Mount("172.17.0.35:/lib", "/tmp/lib", "nfs", uintptr(0), ""); err != nil {
	// 	fmt.Println(err)
	// }

	// To mount NFS, we need to supply "addr=%s" as data option.
	// if err := syscall.Mount("172.17.0.35:/lib", "/tmp/lib", "nfs", uintptr(0), "addr=172.17.0.35"); err != nil {
	// 	fmt.Println(err)
	// }

	// Or we mount using mount(8) tool.
	Mount("172.17.0.16:/lib", "/tmp/lib", "nfs", []string{"ro"})
}

// Mount mounts source to target as fstype with given options. 'source' and 'fstype' must
// be an emtpy string in case it's not required, e.g. for remount, or for auto filesystem
// type, where kernel handles fs type for you. The mount 'options' is a list of options,
// currently come from mount(8), if no more option is required, call Mount with an empty
// string list or nil.
func Mount(source string, target string, fstype string, options []string) error {
	// The remount options to use in case of bind mount. It equals:
	//   options - 'bind' + 'remount' (no duplicate)
	bindRemountOpts := []string{"remount"}
	bind := false

	if options != nil {
		for _, option := range options {
			switch option {
			case "bind":
				bind = true
				break
			case "remount":
				break
			default:
				bindRemountOpts = append(bindRemountOpts, option)
			}
		}
	}

	if bind {
		err := doMount(source, target, fstype, []string{"bind"})
		if err != nil {
			return err
		}
		return doMount(source, target, fstype, bindRemountOpts)
	} else {
		return doMount(source, target, fstype, options)
	}
}

func doMount(source string, target string, fstype string, options []string) error {
	glog.V(5).Infof("Mounting %s %s %s %v", source, target, fstype, options)
	// Build mount command as follows:
	//   mount [-t $fstype] [-o $options] [$source] $target
	mountArgs := []string{"mount"}
	if len(fstype) > 0 {
		mountArgs = append(mountArgs, "-t", fstype)
	}
	if options != nil && len(options) > 0 {
		mountArgs = append(mountArgs, "-o", strings.Join(options, ","))
	}
	if len(source) > 0 {
		mountArgs = append(mountArgs, source)
	}
	mountArgs = append(mountArgs, target)
	command := exec.Command("sudo", mountArgs...)
	output, err := command.CombinedOutput()
	if err != nil {
		glog.Errorf("Mount failed: %v\nMounting arguments: %s %s %s %v\nOutput: %s\n",
			err, source, target, fstype, options, string(output))
	}
	return err
}
