// About DNS in general:
//   https://www.digitalocean.com/community/tutorials/an-introduction-to-dns-terminology-components-and-concepts
// Search domain:
//   http://superuser.com/questions/184361/what-is-the-search-domains-field-for-in-the-tcp-ip-dns-settings-control-panel
//
// Record Types:
//   A: Name -> IP address
//   NS: Name -> Authoritative nameserver ("referrals")
//   MX: Name -> Mail server
//   CNAME: Canonical name
//   PTR: IP address -> Name
//   AAAA: Name -> IPv6 address
// Example1:
//   $ dig www.gatech.edu
//   ;; OPT PSEUDOSECTION:
//   ; EDNS: version: 0, flags:; udp: 4000
//   ;; QUESTION SECTION:
//   ;www.gatech.edu.                        IN      A
//   ;; ANSWER SECTION:
//   www.gatech.edu.         60      IN      CNAME   tlweb.gtm.gatech.edu.
//   tlweb.gtm.gatech.edu.   30      IN      A       130.207.244.165
// The ANSWER SECTION tells that what you asked for is www.gatech.edu., but what
// you really want to ask is tlweb.gtm.gatech.edu (which is a CNAME record). The
// second line returns the IP address for tlweb.gtm.gatech.edu. The number 60, 30
// means TTL for the record.
//
// Example2:
//   $ dig nytimes.com
//   ;; OPT PSEUDOSECTION:
//   ; EDNS: version: 0, flags:; udp: 4000
//   ;; QUESTION SECTION:
//   ;nytimes.com.                   IN      A
//
//   ;; ANSWER SECTION:
//   nytimes.com.            71      IN      A       170.149.172.130
//   nytimes.com.            71      IN      A       170.149.168.130
// The ANSWER SECTION has two records, both belong to nytimes.com., mostly for
// load balance
//
// Example3:
//   $ dig ns gatech.edu
//   $ dig mx gatech.edu
//   $ dig +trace gatech.edu
//   $ dig +trace -x 130.207.7.36

package main
