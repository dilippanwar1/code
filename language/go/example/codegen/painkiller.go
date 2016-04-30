// Run `go generate` in the directory will generate code. `go generate` won't do
// any magic, you'll need to write code to generate code yourself (here we use
// 'stringer' tool. It's more like Makefile.

//go:generate stringer -type=Pill

package painkiller

import "fmt"

type Pill int

const (
	Placebo Pill = iota
	Aspirin
	Ibuprofen
	Paracetamol
	Acetaminophen = Paracetamol
)

func TasteGood(pill Pill) {
	fmt.Printf("You are taking %s", pill)
}
