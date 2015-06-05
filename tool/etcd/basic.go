// curl -L http://127.0.0.1:4001/v2/keys/message
// curl -L http://127.0.0.1:4001/v2/keys/message -XPUT -d value="Awesome"

package main

import (
	"fmt"
	"time"

	"github.com/coreos/go-etcd/etcd"
)

// A thin wrapper around client.Watch to print info.
func watchWrapper(client *etcd.Client, prefix string, waitIndex uint64,
	recursive bool, receiver chan *etcd.Response, stop chan bool) {
	fmt.Println("============================================================")
	fmt.Println("Start longterm watching")
	client.Watch(prefix, waitIndex, recursive, receiver, stop)
	fmt.Println("Stop  longterm watching")
}

func main() {
	client := etcd.NewClient([]string{})

	// Set key "/message" with value. Since etcd use file-system like structure,
	// keys always start with '/'.
	fmt.Println("============================================================")
	fmt.Println("Set initial message")
	resp, err := client.Set("/message", "{Name:Deyuan,Age:25}", 0)
	if err != nil {
		fmt.Println("Error setting key", err)
		return
	}
	fmt.Println(resp.Action)
	fmt.Println(resp.Node)
	fmt.Println(resp.PrevNode)
	fmt.Println(resp.EtcdIndex)

	// Watch signature:
	//   func (c *Client) Watch(prefix string, waitIndex uint64, recursive bool,
	//      receiver chan *Response, stop chan bool) (*Response, error)

	// Wait on key "/message" to reach index 5, it is a one time wait. If current
	// index is larger than or equal 5, the method will return immediately;
	// otherwise, it will block until index reaches 5.
	fmt.Println("============================================================")
	fmt.Println("Start watching on /message index 5")
	client.Watch("/message", 5, false, nil, nil)
	fmt.Println("Stop  watching on /message index 5")

	// When passing 'etcdIncoming' to client.Watch, it is a long term watch. If
	// new change becomes available, client.Watch will block at the channel until
	// someone read from it - it will go on and watch the key again. If a stop
	// channel is given, the client can close long-term watch using the channel.
	// - If wait index is 0, it watches on latest changes, which means Watch will
	//   block immediately, until new change comes.
	// - If wait index is not 0, and is smaller than current key's index, then all
	//   versions from wait index to current index will be listed. E.g. If message
	//   key is already 8, and since we are watching on 5, then index 5,6,7 will
	//   be sent to etcdIncoming channel, then Watch continue watching on latest
	//   changes.
	// - If wait index is not 0, and is larger than current key's index, then
	//   Watch will wait until index reaches wait index. E.g. If message key is
	//   2 and we are watching on 5, then nothing will happen between index 2,3,4.
	//   When index reaches 5, Watch starts sending changes to etcdIncoming.
	etcdIncoming := make(chan *etcd.Response)
	etcdStop := make(chan bool)
	go watchWrapper(client, "/message", 5, false, etcdIncoming, etcdStop)

	for {
		select {
		case resp := <-etcdIncoming:
			fmt.Printf("Incoming etcd event: %+v\n", resp)
			fmt.Println(resp.Node)
			if resp.Action == "delete" {
				etcdStop <- true
				time.Sleep(time.Second) // wait go routine to print.
				return
			}
		}
	}
}
