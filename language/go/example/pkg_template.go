package main

import (
	"html/template"
	"os"
)

type Persion struct {
	Name string
}

func main() {
	// Create a template with a name.
	t := template.New("Example")

	// Field substituition - {{.FieldName}}.
	t, _ = t.Parse("Hello {{.Name}}\n")

	p := Persion{Name: "Mary"}
	t.Execute(os.Stdout, p)
}
