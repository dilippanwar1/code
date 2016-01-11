// +build OMIT

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

// sumFiles returns two channels: one for the results and another for the error
// returned by filepath.Walk. The walk function starts a new goroutine to process
// each regular file, then checks done. If done is closed, the walk stops immediately.
func sumFiles(done chan struct{}, root string) (chan result, chan error) {
	c := make(chan result)
	errc := make(chan error, 1)
	go func() {
		wg := sync.WaitGroup{}

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
			// Read the content in a new goroutine. Note we using goroutine will return
			// immediately from walkFn. Walk will think that processing of the file has
			// complete; so we must use wg.Wait() to wait before all files have acutally
			// been processed.
			wg.Add(1)
			go func() {
				defer wg.Done()
				data, err := ioutil.ReadFile(path)
				select {
				case c <- result{path, md5.Sum(data), err}:
				case <-done:
				}
			}()

			// IMPORTANT: catch done signal here also.
			select {
			case <-done:
				return errors.New("walk canceled")
			default:
				return nil
			}
		})

		// Close result channel when all processings have finished.
		go func() {
			wg.Wait()
			close(c)
		}()

		// Won't block since error is buffered. This is needed in case caller is
		// not interested in error and doesn't read it.
		errc <- err

	}()

	return c, errc
}

// MD5All reads all the files in the file tree rooted at root and returns a map
// from file path to the MD5 sum of the file's contents.  If the directory walk
// fails or any read operation fails, MD5All returns an error.
func MD5All(root string) (map[string][md5.Size]byte, error) {
	m := make(map[string][md5.Size]byte)
	done := make(chan struct{})

	c, errc := sumFiles(done, root)
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
