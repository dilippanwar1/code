package main

import (
	"flag"

	"github.com/golang/glog"
)

func main() {
	// By default, glog logs to temporary directory from os.TempDir(). To log
	// to stdout/stderr, one needs to set flag 'logtostderr'.
	glog.Infof("LooooG")

	// To set from code, there is a hacky way.
	flag.Parse()
	flag.Lookup("logtostderr").Value.Set("true")
	glog.Infof("LOOOOOG")
	glog.Warningf("WARN")
}
