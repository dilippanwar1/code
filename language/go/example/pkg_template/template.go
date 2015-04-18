package main

import (
	"html/template"
	"os"
)

type Person struct {
	Name string
}

func main() {
	// Create a template with a name.
	t := template.New("Example")

	// Parse parses a string into a template, returns a Template struct.
	// Note the syntax for Field substituition, i.e. {{.FieldName}}.
	t, _ = t.Parse("Hello {{.Name}}\n")

	p := Person{Name: "Mary"}
	t.Execute(os.Stdout, p)
}
