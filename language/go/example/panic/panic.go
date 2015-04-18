package main

func Run() {
	panic("panic in Run")
}

func main() {
	// panic in any goroutine will stop execution of entire program.
	go Run()
	select {}
}
