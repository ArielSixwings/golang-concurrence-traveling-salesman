package main

import (
	"fmt"
	"os/exec"
)

func main() {
	runmaster := [24]string{
		"./regions/runmaster/run00.sh",
		"./regions/runmaster/run01.sh",
		"./regions/runmaster/run02.sh",
		"./regions/runmaster/run03.sh",
		"./regions/runmaster/run04.sh",
		"./regions/runmaster/run05.sh",
		"./regions/runmaster/run06.sh",
		"./regions/runmaster/run07.sh",
		"./regions/runmaster/run08.sh",
		"./regions/runmaster/run09.sh",
		"./regions/runmaster/run10.sh",
		"./regions/runmaster/run11.sh",
		"./regions/runmaster/run12.sh",
		"./regions/runmaster/run13.sh",
		"./regions/runmaster/run14.sh",
		"./regions/runmaster/run15.sh",
		"./regions/runmaster/run16.sh",
		"./regions/runmaster/run17.sh",
		"./regions/runmaster/run18.sh",
		"./regions/runmaster/run19.sh",
		"./regions/runmaster/run20.sh",
		"./regions/runmaster/run21.sh",
		"./regions/runmaster/run22.sh",
		"./regions/runmaster/run23.sh"}

	jobs := make(chan int, 24)
	results := make(chan int, 24)

	go worker(jobs, results, runmaster)
	go worker(jobs, results, runmaster)
	go worker(jobs, results, runmaster)
	go worker(jobs, results, runmaster)
	go worker(jobs, results, runmaster)
	go worker(jobs, results, runmaster)

	for i := 0; i < 100; i++ {
		jobs <- i
	}
	close(jobs)

	for j := 0; j < 100; j++ {
		fmt.Println(<-results)
	}
}

func worker(jobs <-chan int, results chan<- int, runmaster [24]string) {
	for n := range jobs {
		results <- RunAll(n, runmaster)
	}
}
func RunAll(n int, runmaster [24]string) int {
	fmt.Println("inside it")

	out, err := exec.Command(runmaster[n]).Output()
	if err != nil {
		fmt.Printf("I found some error to run the PATH: %s", err)
	} else {
		fmt.Println("\nCommand Successfully Executed")
	}
	output := string(out[:])
	fmt.Println(output)
	return n
}
