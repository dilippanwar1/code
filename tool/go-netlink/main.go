package main

import "github.com/vishvananda/netlink"

func main() {
	// Add a new bridge and add eth1 into it.
	la := netlink.NewLinkAttrs()
	la.Name = "foo"
	mybridge := &netlink.Bridge{la}
	_ := netlink.LinkAdd(mybridge)
	eth1, _ := netlink.LinkByName("eth1")
	netlink.LinkSetMaster(eth1, mybridge)

	// Add a new ip address to loopback.
	lo, _ := netlink.LinkByName("lo")
	addr, _ := netlink.ParseAddr("169.254.169.254/32")
	netlink.AddrAdd(lo, addr)
}
