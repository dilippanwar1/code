// Panic in any goroutine will stop execution of entire program.
package main

func Run() {
	panic("panic in Run")
}

func main() {
	go Run()
	select {}
}
