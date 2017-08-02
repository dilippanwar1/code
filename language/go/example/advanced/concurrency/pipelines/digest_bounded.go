// +build OMIT
//
// The pipelie looks like below:
//                        -- digester --
//                       /              \
// walker --> [CH:paths] --- digester ---- [CH:c] --> MD5ALL
//                       \              /
//                        -- digester --
//
// walker sends path to 'paths' channel, which is read by multiple digesters;
// these digesters then write to channel 'c', which is in turn read by MD5ALL.
// To end the pipeline, walker needs to close 'path' channel; digesters will
// need to close 'c' channel. Since digester only use one channel 'c', closing
// the channel is done in MD5ALL with the help of wait group.

package main

import (
	"crypto/md5"
	"errors"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"runtime"
	"sort"
	"sync"
)

type result struct {
	path string
	sum  [md5.Size]byte
	err  error
}

// digester receives work from 'paths' channel, and send result to 'c'.
func digester(done chan struct{}, paths chan string, c chan result) {
	for path := range paths {
		data, err := ioutil.ReadFile(path)
		select {
		case c <- result{path, md5.Sum(data), err}:
		case <-done:
			return
		}
	}
}

// sumFiles returns two channels: one for the results and another for the error
// returned by filepath.Walk. The walk function starts a new goroutine to process
// each regular file, then checks done. If done is closed, the walk stops immediately.
func sumFiles(done chan struct{}, paths chan string, root string) chan error {
	errc := make(chan error, 1)
	go func() {

		// Run the entire tree walk in a goroutine. filepath.Walk returns only after
		// all files have been processed. Also, if any of the walkFn returns non-nil
		// error, Walk will abort early and return that error.
		err := filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
			if err != nil {
				return err
			}
			if !info.Mode().IsRegular() {
				return nil
			}
			select {
			case paths <- path:
				return nil
			case <-done:
				return errors.New("walk canceled")
			default:
				return nil
			}
		})

		close(paths)

		// Won't block since error is buffered. This is needed in case caller is
		// not interested in error and doesn't read it.
		errc <- err

	}()

	return errc
}

// MD5All reads all the files in the file tree rooted at root and returns a map
// from file path to the MD5 sum of the file's contents.  If the directory walk
// fails or any read operation fails, MD5All returns an error.
func MD5All(root string) (map[string][md5.Size]byte, error) {
	c := make(chan result)
	m := make(map[string][md5.Size]byte)
	done := make(chan struct{})
	paths := make(chan string)

	// Create a static number of digester to work on calculating md5 sum.
	wg := sync.WaitGroup{}
	const numDigesters = 20
	wg.Add(numDigesters)
	for i := 0; i < numDigesters; i++ {
		go func() {
			digester(done, paths, c)
			wg.Done()
		}()
	}

	go func() {
		wg.Wait()
		close(c)
	}()

	errc := sumFiles(done, paths, root)
	for data := range c {
		m[data.path] = data.sum
	}

	err := <-errc
	if err != nil {
		return nil, err
	}

	return m, nil
}

func main() {
	// Calculate the MD5 sum of all files under the specified directory,
	// then print the results sorted by path name.
	runtime.GOMAXPROCS(runtime.NumCPU())
	if len(os.Args) != 2 {
		fmt.Printf("Path needed\n")
		os.Exit(1)
	}
	m, err := MD5All(os.Args[1]) // HL
	if err != nil {
		fmt.Println(err)
		return
	}
	var paths []string
	for path := range m {
		paths = append(paths, path)
	}
	sort.Strings(paths) // HL
	for _, path := range paths {
		fmt.Printf("%x  %s\n", m[path], path)
	}
}
