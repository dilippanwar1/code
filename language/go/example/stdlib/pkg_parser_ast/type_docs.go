package main

import (
	"bytes"
	"flag"
	"fmt"
	"go/ast"
	"go/doc"
	"go/parser"
	"go/token"
	"reflect"
	"runtime"
	"strings"
)

var (
	typeSrc = flag.String("s", "./", "From where we are going to read the types")
)

// Pair of strings. We keep the name of fields and the doc.
type Pair struct {
	Name, Doc string
}

// ParseTypes is an array to represent all available types in a parsed file.
type ParseTypes []Pair

// parseDocumentationFrom gets all types' documentation and returns them as an array.
func parseDocumentationFrom(src string) []ParseTypes {
	var docForTypes []ParseTypes

	pkg := astFrom(src)
	// Loop through all type declarations in the package to construct our Name:Doc pair.
	for _, parseType := range pkg.Types {
		if structType, ok := parseType.Decl.Specs[0].(*ast.TypeSpec).Type.(*ast.StructType); ok {
			// If this is a structType; there can be other types, e.g. FuncType. Add the
			// top level struct type to Name:Doc pair.
			var pt ParseTypes
			pt = append(pt, Pair{parseType.Name, fmtRawDoc(parseType.Doc)})

			// Add each fields of the struct to Name:Doc pair.
			for _, field := range structType.Fields.List {
				if n := fieldName(field); n != "-" {
					fieldDoc := fmtRawDoc(field.Doc.Text())
					pt = append(pt, Pair{n, fieldDoc})
				}
			}

			// Finally, append the struct and its fields to final results.
			docForTypes = append(docForTypes, pt)
		}
	}

	return docForTypes
}

// astFrom creates a package document from a file. The specific flow is: parse
// the file to ast, then create a package ast from the single file, then create
// a package doc from the package ast.
func astFrom(filePath string) *doc.Package {
	// Parse given file to ast.File. `fset` is used to hold position information.
	fset := token.NewFileSet()
	f, err := parser.ParseFile(fset, filePath, nil, parser.ParseComments)
	if err != nil {
		fmt.Println(err)
		return nil
	}

	// Create a package node from a set of file nodes. Note error can happen if
	// there is unresolved identifier, etc.
	m := map[string]*ast.File{filePath: f}
	apkg, _ := ast.NewPackage(fset, m, nil, nil)

	return doc.New(apkg, "", 0)
}

// fieldName returns the name of the field as it should appear in JSON format
// "-" indicates that this field is not part of the JSON representation
func fieldName(field *ast.Field) string {
	jsonTag := ""
	if field.Tag != nil {
		jsonTag = reflect.StructTag(field.Tag.Value[1 : len(field.Tag.Value)-1]).Get("json") // Delete first and last quotation
		if strings.Contains(jsonTag, "inline") {
			return "-"
		}
	}

	jsonTag = strings.Split(jsonTag, ",")[0] // This can return "-"
	if jsonTag == "" {
		if field.Names != nil {
			return field.Names[0].Name
		}
		return field.Type.(*ast.Ident).Name
	}
	return jsonTag
}

// fmtRawDoc converts raw doc to formatted doc.
func fmtRawDoc(rawDoc string) string {
	var buffer bytes.Buffer
	delPrevChar := func() {
		if buffer.Len() > 0 {
			buffer.Truncate(buffer.Len() - 1) // Delete the last " " or "\n"
		}
	}

	// Ignore all lines after ---
	rawDoc = strings.Split(rawDoc, "---")[0]

	for _, line := range strings.Split(rawDoc, "\n") {
		line = strings.TrimRight(line, " ")
		leading := strings.TrimLeft(line, " ")
		switch {
		case len(line) == 0: // Keep paragraphs
			delPrevChar()
			buffer.WriteString("\n\n")
		case strings.HasPrefix(leading, "TODO"): // Ignore one line TODOs
		case strings.HasPrefix(leading, "+"): // Ignore instructions to go2idl
		default:
			if strings.HasPrefix(line, " ") || strings.HasPrefix(line, "\t") {
				delPrevChar()
				line = "\n" + line + "\n" // Replace it with newline. This is useful when we have a line with: "Example:\n\tJSON-someting..."
			} else {
				line += " "
			}
			buffer.WriteString(line)
		}
	}

	postDoc := strings.TrimRight(buffer.String(), "\n")
	postDoc = strings.Replace(postDoc, "\\\"", "\"", -1) // replace user's \" to "
	postDoc = strings.Replace(postDoc, "\"", "\\\"", -1) // Escape "
	postDoc = strings.Replace(postDoc, "\n", "\\n", -1)
	postDoc = strings.Replace(postDoc, "\t", "\\t", -1)

	return postDoc
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	flag.Parse()

	docForTypes := parseDocumentationFrom(*typeSrc)
	for _, docForType := range docForTypes {
		fmt.Println(docForType)
	}
}
