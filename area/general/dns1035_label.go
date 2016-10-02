package main

import (
	"fmt"
	"regexp"
)

const dns1035LabelFmt string = "[a-z]([-a-z0-9]*[a-z0-9])?"
const DNS1035LabelMaxLength int = 63

var dns1035LabelRegexp = regexp.MustCompile("^" + dns1035LabelFmt + "$")

// MaxLenError returns a string explanation of a "string too long" validation
// failure.
func MaxLenError(length int) string {
	return fmt.Sprintf("must be no more than %d characters", length)
}

// RegexError returns a string explanation of a regex validation failure.
func RegexError(fmt string, examples ...string) string {
	s := "must match the regex " + fmt
	if len(examples) == 0 {
		return s
	}
	s += " (e.g. "
	for i := range examples {
		if i > 0 {
			s += " or "
		}
		s += "'" + examples[i] + "'"
	}
	return s + ")"
}

// IsDNS1035Label tests for a string that conforms to the definition of a label in
// DNS (RFC 1035).
func IsDNS1035Label(value string) []string {
	var errs []string
	if len(value) > DNS1035LabelMaxLength {
		errs = append(errs, MaxLenError(DNS1035LabelMaxLength))
	}
	if !dns1035LabelRegexp.MatchString(value) {
		errs = append(errs, RegexError(dns1035LabelFmt, "my-name", "abc-123"))
	}
	return errs
}

func main() {
	fmt.Println(IsDNS1035Label("docker-registry.caicloudprivatetest.com"))
}
