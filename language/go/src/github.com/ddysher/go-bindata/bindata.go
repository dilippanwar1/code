package main

import (
	"bytes"
	"compress/gzip"
	"fmt"
	"io"
	"strings"
	"os"
	"time"
	"io/ioutil"
	"path"
	"path/filepath"
)

func bindata_read(data []byte, name string) ([]byte, error) {
	gz, err := gzip.NewReader(bytes.NewBuffer(data))
	if err != nil {
		return nil, fmt.Errorf("Read %q: %v", name, err)
	}

	var buf bytes.Buffer
	_, err = io.Copy(&buf, gz)
	gz.Close()

	if err != nil {
		return nil, fmt.Errorf("Read %q: %v", name, err)
	}

	return buf.Bytes(), nil
}

type asset struct {
	bytes []byte
	info  os.FileInfo
}

type bindata_file_info struct {
	name string
	size int64
	mode os.FileMode
	modTime time.Time
}

func (fi bindata_file_info) Name() string {
	return fi.name
}
func (fi bindata_file_info) Size() int64 {
	return fi.size
}
func (fi bindata_file_info) Mode() os.FileMode {
	return fi.mode
}
func (fi bindata_file_info) ModTime() time.Time {
	return fi.modTime
}
func (fi bindata_file_info) IsDir() bool {
	return false
}
func (fi bindata_file_info) Sys() interface{} {
	return nil
}

var _golden_alpha_txt = []byte("\x1f\x8b\x08\x00\x00\x09\x6e\x88\x00\xff\x4a\x4c\x4a\x4e\x49\x4d\x4b\xe7\x02\x04\x00\x00\xff\xff\x24\x2a\x53\x0d\x08\x00\x00\x00")

func golden_alpha_txt_bytes() ([]byte, error) {
	return bindata_read(
		_golden_alpha_txt,
		"golden/alpha.txt",
	)
}

func golden_alpha_txt() (*asset, error) {
	bytes, err := golden_alpha_txt_bytes()
	if err != nil {
		return nil, err
	}

	info := bindata_file_info{name: "golden/alpha.txt", size: 8, mode: os.FileMode(436), modTime: time.Unix(1421512536, 0)}
	a := &asset{bytes: bytes, info:  info}
	return a, nil
}

var _golden_file1_go = []byte("\x1f\x8b\x08\x00\x00\x09\x6e\x88\x00\xff\x01\x00\x00\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00")

func golden_file1_go_bytes() ([]byte, error) {
	return bindata_read(
		_golden_file1_go,
		"golden/file1.go",
	)
}

func golden_file1_go() (*asset, error) {
	bytes, err := golden_file1_go_bytes()
	if err != nil {
		return nil, err
	}

	info := bindata_file_info{name: "golden/file1.go", size: 0, mode: os.FileMode(436), modTime: time.Unix(1421512536, 0)}
	a := &asset{bytes: bytes, info:  info}
	return a, nil
}

var _golden_index_html = []byte("\x1f\x8b\x08\x00\x00\x09\x6e\x88\x00\xff\xb2\xc9\x28\xc9\xcd\xb1\xe3\xb2\xd1\x87\xd0\x80\x00\x00\x00\xff\xff\x55\xf6\x9c\xbe\x0f\x00\x00\x00")

func golden_index_html_bytes() ([]byte, error) {
	return bindata_read(
		_golden_index_html,
		"golden/index.html",
	)
}

func golden_index_html() (*asset, error) {
	bytes, err := golden_index_html_bytes()
	if err != nil {
		return nil, err
	}

	info := bindata_file_info{name: "golden/index.html", size: 15, mode: os.FileMode(436), modTime: time.Unix(1421512536, 0)}
	a := &asset{bytes: bytes, info:  info}
	return a, nil
}

var _golden_love_c = []byte("\x1f\x8b\x08\x00\x00\x09\x6e\x88\x00\xff\x74\x8f\x41\x6f\x83\x30\x0c\x85\xef\xf9\x15\x6f\x4c\x4c\x64\x43\x1b\x3b\xb3\xed\xb6\x3f\xd0\x73\x2f\x94\x18\x11\x09\x4c\x95\x84\xf6\x50\xf1\xdf\xeb\x94\xa6\xe2\xd2\x9b\xed\xf7\x6c\x7f\xef\xd5\x72\x3b\xcc\x86\xf0\xe3\x83\xb1\xd3\x67\xff\xa7\x94\xe5\x80\xb1\xb1\x5c\x68\x75\x51\x40\x6c\xb9\x84\xa3\x13\x39\x4f\xf8\x45\x55\x2b\x19\x1f\x9d\x08\x5d\x91\xfd\x73\x20\x87\x06\x3c\x8f\x07\x29\xc2\x94\x9c\x7b\xce\x74\x2d\x46\xdf\x36\x2c\xbe\xdc\x64\xe5\x1b\xeb\xdb\xee\xb9\xb7\x03\xa1\x60\xbc\xc8\x35\x8d\xf8\x05\x9b\x07\xa9\x7a\xc7\x77\x55\x3f\xd1\x3e\xc0\x79\x52\x59\xe6\xfc\xb5\x76\xcb\x96\x6d\x77\x37\x4f\x1d\x28\x62\x92\x49\x98\xd6\xcb\x4e\x6e\x84\xf1\x91\x6c\x45\x73\x14\x66\xc7\x31\xe3\xa2\xae\x01\x00\x00\xff\xff\x95\x67\x41\xc0\x1d\x01\x00\x00")

func golden_love_c_bytes() ([]byte, error) {
	return bindata_read(
		_golden_love_c,
		"golden/love.c",
	)
}

func golden_love_c() (*asset, error) {
	bytes, err := golden_love_c_bytes()
	if err != nil {
		return nil, err
	}

	info := bindata_file_info{name: "golden/love.c", size: 285, mode: os.FileMode(436), modTime: time.Unix(1421512536, 0)}
	a := &asset{bytes: bytes, info:  info}
	return a, nil
}

// Asset loads and returns the asset for the given name.
// It returns an error if the asset could not be found or
// could not be loaded.
func Asset(name string) ([]byte, error) {
	cannonicalName := strings.Replace(name, "\\", "/", -1)
	if f, ok := _bindata[cannonicalName]; ok {
		a, err := f()
		if err != nil {
			return nil, fmt.Errorf("Asset %s can't read by error: %v", name, err)
		}
		return a.bytes, nil
	}
	return nil, fmt.Errorf("Asset %s not found", name)
}

// AssetInfo loads and returns the asset info for the given name.
// It returns an error if the asset could not be found or
// could not be loaded.
func AssetInfo(name string) (os.FileInfo, error) {
	cannonicalName := strings.Replace(name, "\\", "/", -1)
	if f, ok := _bindata[cannonicalName]; ok {
		a, err := f()
		if err != nil {
			return nil, fmt.Errorf("AssetInfo %s can't read by error: %v", name, err)
		}
		return a.info, nil
	}
	return nil, fmt.Errorf("AssetInfo %s not found", name)
}

// AssetNames returns the names of the assets.
func AssetNames() []string {
	names := make([]string, 0, len(_bindata))
	for name := range _bindata {
		names = append(names, name)
	}
	return names
}

// _bindata is a table, holding each asset generator, mapped to its name.
var _bindata = map[string]func() (*asset, error){
	"golden/alpha.txt": golden_alpha_txt,
	"golden/file1.go": golden_file1_go,
	"golden/index.html": golden_index_html,
	"golden/love.c": golden_love_c,
}

// AssetDir returns the file names below a certain
// directory embedded in the file by go-bindata.
// For example if you run go-bindata on data/... and data contains the
// following hierarchy:
//     data/
//       foo.txt
//       img/
//         a.png
//         b.png
// then AssetDir("data") would return []string{"foo.txt", "img"}
// AssetDir("data/img") would return []string{"a.png", "b.png"}
// AssetDir("foo.txt") and AssetDir("notexist") would return an error
// AssetDir("") will return []string{"data"}.
func AssetDir(name string) ([]string, error) {
	node := _bintree
	if len(name) != 0 {
		cannonicalName := strings.Replace(name, "\\", "/", -1)
		pathList := strings.Split(cannonicalName, "/")
		for _, p := range pathList {
			node = node.Children[p]
			if node == nil {
				return nil, fmt.Errorf("Asset %s not found", name)
			}
		}
	}
	if node.Func != nil {
		return nil, fmt.Errorf("Asset %s not found", name)
	}
	rv := make([]string, 0, len(node.Children))
	for name := range node.Children {
		rv = append(rv, name)
	}
	return rv, nil
}

type _bintree_t struct {
	Func func() (*asset, error)
	Children map[string]*_bintree_t
}
var _bintree = &_bintree_t{nil, map[string]*_bintree_t{
	"golden": &_bintree_t{nil, map[string]*_bintree_t{
		"alpha.txt": &_bintree_t{golden_alpha_txt, map[string]*_bintree_t{
		}},
		"file1.go": &_bintree_t{golden_file1_go, map[string]*_bintree_t{
		}},
		"index.html": &_bintree_t{golden_index_html, map[string]*_bintree_t{
		}},
		"love.c": &_bintree_t{golden_love_c, map[string]*_bintree_t{
		}},
	}},
}}

// Restore an asset under the given directory
func RestoreAsset(dir, name string) error {
        data, err := Asset(name)
        if err != nil {
                return err
        }
        info, err := AssetInfo(name)
        if err != nil {
                return err
        }
        err = os.MkdirAll(_filePath(dir, path.Dir(name)), os.FileMode(0755))
        if err != nil {
                return err
        }
        err = ioutil.WriteFile(_filePath(dir, name), data, info.Mode())
        if err != nil {
                return err
        }
        err = os.Chtimes(_filePath(dir, name), info.ModTime(), info.ModTime())
        if err != nil {
                return err
        }
        return nil
}

// Restore assets under the given directory recursively
func RestoreAssets(dir, name string) error {
        children, err := AssetDir(name)
        if err != nil { // File
                return RestoreAsset(dir, name)
        } else { // Dir
                for _, child := range children {
                        err = RestoreAssets(dir, path.Join(name, child))
                        if err != nil {
                                return err
                        }
                }
        }
        return nil
}

func _filePath(dir, name string) string {
        cannonicalName := strings.Replace(name, "\\", "/", -1)
        return filepath.Join(append([]string{dir}, strings.Split(cannonicalName, "/")...)...)
}

