// Run with:
//   "go test ."

package assert_test

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSomething(t *testing.T) {

	// In testify, assert.Equal uses 'reflect.DeepEqual' to compare value.

	// assert equality
	assert.Equal(t, 123, 123, "they should be equal")

	// assert inequality
	assert.NotEqual(t, 123, 456, "they should not be equal")

	// In testify, assert.Nil uses "= nil" and package 'reflect' to compare value.
	object := 2

	// assert for nil (good for errors)
	assert.Nil(t, object, "object should be nil")
}
