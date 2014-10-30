// Go net.IPNet example.
//   go run pkg_net_ipnet.go 192.168.1.1/24
package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	var name string
	if len(os.Args) != 2 {
		name = "192.168.1.1/24"
	} else {
		name = os.Args[1]
	}

	addr, ipnet, _ := net.ParseCIDR(name)
	fmt.Println(addr)
	fmt.Println(ipnet)

	ip1 := net.ParseIP("192.168.1.12")
	ip2 := net.ParseIP("192.168.2.12")
	fmt.Println(ipnet.Contains(ip1))
	fmt.Println(ipnet.Contains(ip2))
	fmt.Println(ipSub(ip2, ip1))
}

// Subtract two IPs, returning the difference as an offset - used or splitting an IP into
// network addr and host addr parts.
func ipSub(lhs, rhs net.IP) int {
	// If they are not the same length, normalize them.  Make copies because net.IP is
	// a slice underneath. Sneaky sneaky.
	lhs = simplifyIP(lhs)
	rhs = simplifyIP(rhs)
	if len(lhs) != len(rhs) {
		lhs = copyIP(lhs).To16()
		rhs = copyIP(rhs).To16()
	}
	offset := 0
	borrow := 0
	// Loop from most-significant to least.
	for i := range lhs {
		offset <<= 8
		result := (int(lhs[i]) - borrow) - int(rhs[i])
		if result < 0 {
			borrow = 1
		} else {
			borrow = 0
		}
		offset += result
	}
	return offset
}

// Get the optimal slice for an IP. IPv4 addresses will come back in a 4 byte slice. IPv6
// addresses will come back in a 16 byte slice. Non-IP arguments will produce nil.
func simplifyIP(in net.IP) net.IP {
	if ip4 := in.To4(); ip4 != nil {
		return ip4
	}
	return in.To16()
}

// Make a copy of a net.IP.  It appears to be a value type, but it is actually defined as a
// slice, so value assignment is shallow.  Why does a poor dumb user like me need to know
// this sort of implementation detail?
func copyIP(in net.IP) net.IP {
	out := make(net.IP, len(in))
	copy(out, in)
	return out
}
