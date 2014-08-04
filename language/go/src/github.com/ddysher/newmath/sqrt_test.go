// You write a test by creating a file with a name ending in _test.go that
// contains functions named TestXXX with signature func (t *testing.T).
// The test framework runs each such function; if the function calls a
// failure function such as t.Error or t.Fail, the test is considered to
// have failed.
package newmath

import "testing"

func TestSqrt(t *testing.T) {
	const in, out = 4, 2
	if x := Sqrt(in); x != out {
		t.Errorf("Sqrt(%v) = %v, want %v", in, x, out)
	}
}
