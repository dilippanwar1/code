package main

import (
	"fmt"
	"net"
	"reflect"
)

func main() {
	ParseIP()
	ParseCIDR()
	Mask()
	Misc()
}

func ParseIP() {
	// net.ParseIP parses string representation of an ip address to IP struct.
	addr := net.ParseIP("127.0.0.1")

	// Print the dotted IPv4 or colon IPv6 address (net.IP implemented the
	// Stringer interface, which has a method String() used to print value).
	fmt.Println(addr)
	fmt.Println(reflect.TypeOf(addr)) // net.IP

	if addr == nil {
		fmt.Println("Invalid address")
	} else {
		fmt.Println("The address is", addr.String())
	}
}

func ParseCIDR() {
	// ParseCIDR parses s as a CIDR notation IP address and mask, like
	// "192.168.100.1/24" or "2001:DB8::/48". It returns (IP, *IPNet, error).
	addr, ipnet, err := net.ParseCIDR("192.168.1.1/24")
	if err != nil {
		fmt.Println("Invalid cidr address")
		return
	}
	fmt.Println(addr)  // 192.168.1.1
	fmt.Println(ipnet) // 192.168.1.0/24 (Note the last hex becomes 0)

	ip1 := net.ParseIP("192.168.1.12")
	ip2 := net.ParseIP("192.168.2.12")
	fmt.Println(ipnet.Contains(ip1)) // true
	fmt.Println(ipnet.Contains(ip2)) // false
}

func Mask() {
	addr := net.ParseIP("64.233.177.113")
	mask := addr.DefaultMask()
	network := addr.Mask(mask)
	ones, bits := mask.Size()
	fmt.Println("Address is", addr.String(),
		"\nDefault mask length is", bits,
		"\nLeading ones count is", ones,
		"\nMask is (hex)", mask.String(),
		"\nNetwork is", network.String())
}

func Misc() {
	ip1 := net.ParseIP("192.168.1.12")
	ip2 := net.ParseIP("192.168.2.12")
	fmt.Println(ipSub(ip2, ip1))
}

// Subtract two IPs, returning the difference as an offset - used or splitting an IP
// into network addr and host addr parts.
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
