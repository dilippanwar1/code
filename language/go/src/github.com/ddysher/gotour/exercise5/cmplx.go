// Let's explore Go's built-in support for complex numbers via
// the complex64 and complex128 types.

package main
 
import (
  "fmt"
  "math/cmplx"
)
 
func Cbrt(x complex128) complex128 {
  z := complex128(2)
  s := complex128(0)
  for {
    z = z - (cmplx.Pow(z,3) - x)/(3 * (z * z))
    if cmplx.Abs(s-z) < 1e-17 {
      break
    }
    s = z
  }
  return z
}
 
func main() {
  fmt.Println(Cbrt(2))
}
