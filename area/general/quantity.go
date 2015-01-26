// The serialization format is:
//
// <quantity>        ::= <signedNumber><suffix>
//   (Note that <suffix> may be empty, from the "" case in <decimalSI>.)
// <digit>           ::= 0 | 1 | ... | 9
// <digits>          ::= <digit> | <digit><digits>
// <number>          ::= <digits> | <digits>.<digits> | <digits>. | .<digits>
// <sign>            ::= "+" | "-"
// <signedNumber>    ::= <number> | <sign><number>
// <suffix>          ::= <binarySI> | <decimalExponent> | <decimalSI>
// <binarySI>        ::= Ki | Mi | Gi | Ti | Pi | Ei
//   (International System of units; See: http://physics.nist.gov/cuu/Units/binary.html)
// <decimalSI>       ::= m | "" | k | M | G | T | P | E
//   (Note that 1024 = 1Ki but 1000 = 1k; I didn't choose the capitalization.)
// <decimalExponent> ::= "e" <signedNumber> | "E" <signedNumber>

package main

import (
	"fmt"
	"math/big"
	"os"
	"regexp"

	"strconv"
	"strings"

	"speter.net/go/exp/math/dec/inf"
)

type Quantity struct {
	// Amount is public, so you can manipulate it if the accessor
	// functions are not sufficient.
	Amount *inf.Dec

	// Change Format at will. See the comment for Canonicalize for
	// more details.
	Format
}

type Format string

func (q *Quantity) Canonicalize() (string, suffix) {
	if q.Amount == nil {
		return "0", ""
	}

	format := q.Format
	switch format {
	case DecimalExponent, DecimalSI:
	case BinarySI:
		if q.Amount.Cmp(decMinus1024) > 0 && q.Amount.Cmp(dec1024) < 0 {
			// This avoids rounding and hopefully confusion, too.
			format = DecimalSI
		} else {
			tmp := &inf.Dec{}
			tmp.Round(q.Amount, 0, inf.RoundUp)
			if tmp.Cmp(q.Amount) != 0 {
				// Don't lose precision-- show as DecimalSI
				format = DecimalSI
			}
		}
	default:
		format = DecimalExponent
	}

	// TODO: If BinarySI formatting is requested but would cause rounding, upgrade to
	// one of the other formats.
	switch format {
	case DecimalExponent, DecimalSI:
		mantissa := q.Amount.UnscaledBig()
		exponent := int(-q.Amount.Scale())
		amount := big.NewInt(0).Set(mantissa)
		// move all factors of 10 into the exponent for easy reasoning
		amount, times := removeFactors(amount, bigTen)
		exponent += times

		// make sure exponent is a multiple of 3
		for exponent%3 != 0 {
			amount.Mul(amount, bigTen)
			exponent--
		}

		suffix, _ := quantitySuffixer.construct(10, exponent, format)
		number := amount.String()
		return number, suffix
	case BinarySI:
		tmp := &inf.Dec{}
		tmp.Round(q.Amount, 0, inf.RoundUp)

		amount, exponent := removeFactors(tmp.UnscaledBig(), big1024)
		suffix, _ := quantitySuffixer.construct(2, exponent*10, format)
		number := amount.String()
		return number, suffix
	}
	return "0", ""
}

// removeFactors divides in a loop; the return values have the property that
// d == result * factor ^ times
// d may be modified in place.
// If d == 0, then the return values will be (0, 0)
func removeFactors(d, factor *big.Int) (result *big.Int, times int) {
	q := big.NewInt(0)
	m := big.NewInt(0)
	for d.Cmp(bigZero) != 0 {
		q.DivMod(d, factor, m)
		if m.Cmp(bigZero) != 0 {
			break
		}
		times++
		d, q = q, d
	}
	return d, times
}

const (
	splitREString = "^([+-]?[0-9.]+)([eEimkKMGTP]*[-+]?[0-9]*)$"

	DecimalExponent = Format("DecimalExponent") // e.g., 12e6
	BinarySI        = Format("BinarySI")        // e.g., 12Mi (12 * 2^20)
	DecimalSI       = Format("DecimalSI")       // e.g., 12M  (12 * 10^6)
)

var (
	splitRE = regexp.MustCompile(splitREString)

	// Commonly needed big.Int values-- treat as read only!
	bigTen      = big.NewInt(10)
	bigZero     = big.NewInt(0)
	bigOne      = big.NewInt(1)
	bigThousand = big.NewInt(1000)
	big1024     = big.NewInt(1024)

	// Commonly needed inf.Dec values-- treat as read only!
	decZero      = inf.NewDec(0, 0)
	decOne       = inf.NewDec(1, 0)
	decMinusOne  = inf.NewDec(-1, 0)
	decThousand  = inf.NewDec(1000, 0)
	dec1024      = inf.NewDec(1024, 0)
	decMinus1024 = inf.NewDec(-1024, 0)

	// Largest (in magnitude) number allowed.
	maxAllowed = inf.NewDec((1<<63)-1, 0) // == max int64

	// The maximum value we can represent milli-units for.
	// Compare with the return value of Quantity.Value() to
	// see if it's safe to use Quantity.MilliValue().
	MaxMilliValue = int64(((1 << 63) - 1) / 1000)
)

type suffix string

// suffixer can interpret and construct suffixes.
type suffixer interface {
	interpret(suffix) (base, exponent int, fmt Format, ok bool)
	construct(base, exponent int, fmt Format) (s suffix, ok bool)
}

// quantitySuffixer handles suffixes for all three formats that quantity
// can handle.
var quantitySuffixer = newSuffixer()

type bePair struct {
	base, exponent int
}

type listSuffixer struct {
	suffixToBE map[suffix]bePair
	beToSuffix map[bePair]suffix
}

func (ls *listSuffixer) addSuffix(s suffix, pair bePair) {
	if ls.suffixToBE == nil {
		ls.suffixToBE = map[suffix]bePair{}
	}
	if ls.beToSuffix == nil {
		ls.beToSuffix = map[bePair]suffix{}
	}
	ls.suffixToBE[s] = pair
	ls.beToSuffix[pair] = s
}

func (ls *listSuffixer) lookup(s suffix) (base, exponent int, ok bool) {
	pair, ok := ls.suffixToBE[s]
	if !ok {
		return 0, 0, false
	}
	return pair.base, pair.exponent, true
}

func (ls *listSuffixer) construct(base, exponent int) (s suffix, ok bool) {
	s, ok = ls.beToSuffix[bePair{base, exponent}]
	return
}

type suffixHandler struct {
	decSuffixes listSuffixer
	binSuffixes listSuffixer
}

func newSuffixer() suffixer {
	sh := &suffixHandler{}

	sh.binSuffixes.addSuffix("Ki", bePair{2, 10})
	sh.binSuffixes.addSuffix("Mi", bePair{2, 20})
	sh.binSuffixes.addSuffix("Gi", bePair{2, 30})
	sh.binSuffixes.addSuffix("Ti", bePair{2, 40})
	sh.binSuffixes.addSuffix("Pi", bePair{2, 50})
	sh.binSuffixes.addSuffix("Ei", bePair{2, 60})
	// Don't emit an error when trying to produce
	// a suffix for 2^0.
	sh.decSuffixes.addSuffix("", bePair{2, 0})

	sh.decSuffixes.addSuffix("m", bePair{10, -3})
	sh.decSuffixes.addSuffix("", bePair{10, 0})
	sh.decSuffixes.addSuffix("k", bePair{10, 3})
	sh.decSuffixes.addSuffix("M", bePair{10, 6})
	sh.decSuffixes.addSuffix("G", bePair{10, 9})
	sh.decSuffixes.addSuffix("T", bePair{10, 12})
	sh.decSuffixes.addSuffix("P", bePair{10, 15})
	sh.decSuffixes.addSuffix("E", bePair{10, 18})

	return sh
}

func (sh *suffixHandler) construct(base, exponent int, fmt Format) (s suffix, ok bool) {
	switch fmt {
	case DecimalSI:
		return sh.decSuffixes.construct(base, exponent)
	case BinarySI:
		return sh.binSuffixes.construct(base, exponent)
	case DecimalExponent:
		if base != 10 {
			return "", false
		}
		if exponent == 0 {
			return "", true
		}
		return suffix("e" + strconv.FormatInt(int64(exponent), 10)), true
	}
	return "", false
}

func (sh *suffixHandler) interpret(suffix suffix) (base, exponent int, fmt Format, ok bool) {
	// Try lookup tables first
	if b, e, ok := sh.decSuffixes.lookup(suffix); ok {
		return b, e, DecimalSI, true
	}
	if b, e, ok := sh.binSuffixes.lookup(suffix); ok {
		return b, e, BinarySI, true
	}

	if len(suffix) > 1 && (suffix[0] == 'E' || suffix[0] == 'e') {
		parsed, err := strconv.ParseInt(string(suffix[1:]), 10, 64)
		if err != nil {
			return 0, 0, DecimalExponent, false
		}
		return 10, int(parsed), DecimalExponent, true
	}

	return 0, 0, DecimalExponent, false
}

func main() {
	// str examples:
	//   6.1Gi (6.1 * 2^30)
	//   6.1G (6.1 * 10^9)
	//   12M (12 * 10^6)
	//   1e6 (decimal exponents)

	str := "6.1Gi"
	parts := splitRE.FindStringSubmatch(strings.TrimSpace(str))
	if len(parts) != 3 {
		fmt.Println("error find string submatch")
		os.Exit(1)
	}

	amount := new(inf.Dec)
	fmt.Println("Parsed part[1]:", parts[1]) // e.g. for 6.1Gi: 6.1; for 6.1G: 6.1.
	// Note in pkg dec, scale is the scale of coefficient, e.g. when passing 6.1,
	// the value amount.Scale() is 1, 6.11 is 2, 61 is 0, 611 is 0.
	if _, ok := amount.SetString(parts[1]); !ok {
		fmt.Println("error set amount string")
		os.Exit(1)
	}

	fmt.Println("Parsed part[2]:", parts[2]) // e.g. for 6.1Gi: Gi; for 6.1G: G.
	// e.g. for 6.1Gi, base=2, exponent=30, format=BinarySI;
	//      for 6.1G, base=10, exponent=9, format=DecimalSI.
	base, exponent, format, ok := quantitySuffixer.interpret(suffix(parts[2]))
	if !ok {
		fmt.Println("error parsing suffxi")
		os.Exit(1)
	}

	// No one but us has to think about suffixes, remove it.
	if base == 10 {
		amount.SetScale(amount.Scale() + inf.Scale(-exponent))
	} else if base == 2 {
		// numericSuffix = 2 ** exponent
		numericSuffix := big.NewInt(1).Lsh(bigOne, uint(exponent))
		ub := amount.UnscaledBig()
		amount.SetUnscaledBig(ub.Mul(ub, numericSuffix))
	}

	// Cap at min/max bounds.
	sign := amount.Sign()
	if sign == -1 {
		amount.Neg(amount)
	}
	// This rounds non-zero values up to the minimum representable
	// value, under the theory that if you want some resources, you
	// should get some resources, even if you asked for way too small
	// of an amount.
	// Arguably, this should be inf.RoundHalfUp (normal rounding), but
	// that would have the side effect of rounding values < .5m to zero.
	amount.Round(amount, 3, inf.RoundUp)

	// The max is just a simple cap.
	if amount.Cmp(maxAllowed) > 0 {
		amount.Set(maxAllowed)
	}
	if format == BinarySI && amount.Cmp(decOne) < 0 && amount.Cmp(decZero) > 0 {
		// This avoids rounding and hopefully confusion, too.
		format = DecimalSI
	}
	if sign == -1 {
		amount.Neg(amount)
	}

	quantity := Quantity{amount, format}
	fmt.Println(quantity)
	canonical, suffix := quantity.Canonicalize()
	fmt.Println(canonical, suffix)
}
