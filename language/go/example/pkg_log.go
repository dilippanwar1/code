package main

import (
	"io"
	"io/ioutil"
	"log"
	"os"
)

var (
	Trace *log.Logger
	Info  *log.Logger
	Warn  *log.Logger
	Error *log.Logger
	File  *log.Logger
	Multi *log.Logger
)

func Init(traceHandle io.Writer, infoHandle io.Writer, warningHandle io.Writer, errorHandle io.Writer) {

	Trace = log.New(traceHandle, "Trace: ", log.Ldate|log.Ltime|log.Lshortfile)
	Info = log.New(infoHandle, "Info: ", log.Ldate|log.Ltime|log.Lshortfile)
	Warn = log.New(warningHandle, "Warn: ", log.Ldate|log.Ltime|log.Lshortfile)
	Error = log.New(errorHandle, "Error: ", log.Ldate|log.Ltime|log.Lshortfile)

	// Log to file.
	file, err := os.OpenFile("File.txt", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666)
	if err != nil {
		return
	}
	File = log.New(file, "File Log: ", log.Ldate|log.Ltime|log.Lshortfile)

	// Log to file and stdout.
	Multi = log.New(io.MultiWriter(file, os.Stdout), "Multi Log: ",
		log.Ldate|log.Ltime|log.Lshortfile)
}

func main() {
	Init(ioutil.Discard, os.Stdout, os.Stdout, os.Stdout)

	// Use standard configuration.
	log.Println("Hello, Basic Log")

	// Remove flag configuration, default is 3.
	log.SetFlags(0)
	log.Println("Hello, Removed log configuration")

	log.SetOutput(ioutil.Discard)
	log.Println("Hello, Discared log")

	Trace.Println("Trace information")
	Info.Println("Info information")
	Warn.Println("Warn information")
	Error.Println("Error information")
	File.Println("Print to file")
	Multi.Println("Print to file and stdout")
}
