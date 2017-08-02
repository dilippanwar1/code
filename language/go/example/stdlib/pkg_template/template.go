package main

import (
	"html/template"
	"os"
)

func main() {
	fileTemplate()
}

type Person struct {
	Name string
}

func simpleTemplate() {
	// Create a template with a name.
	t := template.New("Example")

	// Parse parses a string into a template, returns a Template struct.
	// Note the syntax for Field substituition, i.e. {{.FieldName}}.
	t, _ = t.Parse("Hello {{.Name}}\n")

	p := Person{Name: "Mary"}
	t.Execute(os.Stdout, p)
}

type ConfigToYaml struct {
	Volumes      map[string]string
	VolumeMounts map[string]string
}

func fileTemplate() {
	t, _ := template.ParseFiles("k8s_pod.yaml.tmpl") //setp 1
	t.Execute(os.Stdout, ConfigToYaml{
		Volumes:      map[string]string{"vvv1": "/mnt/fast", "vvv2": "/mnt/slow"},
		VolumeMounts: map[string]string{"vvv1": "/local-fast", "vvv2": "/local-slow"},
	})
}
