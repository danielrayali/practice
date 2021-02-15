package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

// Checks whether a value is within at least one of the ranges.
// It returns true if it is at least in one range, false otherwise.
func in_range(ranges [][]int, value int) bool {
	for i := 0; i < len(ranges); i++ {
		if value >= ranges[i][0] && value <= ranges[i][1] {
			return true
		}
	}
	return false
}

// Returns a list of values that are not atleast within one of the ranges.
// ticket_str is expected to be 3 comma separated values e.g. "1,2,3".
// Each value of ticket_str is processed individually
func get_out_of_range(ranges [][]int, ticket_str string) []int {
	var ticket_values = strings.Split(ticket_str, ",")
	var out_of_range []int
	for i := 0; i < len(ticket_values); i++ {
		value, err := strconv.Atoi(ticket_values[i])
		if err != nil {
			log.Fatal(err)
		}
		if !in_range(ranges, value) {
			log.Println("Out of range value found:", value)
			out_of_range = append(out_of_range, value)
		}
	}
	return out_of_range
}

func main() {
	file, err := os.Open("./d16s1.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// Read fields
	scanner := bufio.NewScanner(file)
	scanner.Scan()
	var all_ranges [][]int

	// Scan() and Text() remove newlines (all spaces?), check for empty string
	for scanner.Text() != "" {
		log.Println("Read:", scanner.Text())
		halves := strings.Split(scanner.Text(), ": ")
		ranges := strings.Split(halves[1], " or ")
		for i := 0; i < len(ranges); i++ {
			var max_min = strings.Split(ranges[i], "-")
			var range_min, min_err = strconv.Atoi(max_min[0])
			if min_err != nil {
				log.Fatal(min_err)
			}
			var range_max, max_err = strconv.Atoi(max_min[1])
			if max_err != nil {
				log.Fatal(max_err)
			}
			all_ranges = append(all_ranges, []int{range_min, range_max})
		}
		scanner.Scan()
	}
	log.Printf("Ranges: %d\n", all_ranges)

	scanner.Scan() // Reads "your ticket:"
	scanner.Scan() // Reads the ticket values

	var out_of_range []int
	out_of_range = append(out_of_range, get_out_of_range(all_ranges, scanner.Text())...)

	scanner.Scan() // Reads newline
	scanner.Scan() // Reads "nearby tickets:"

	// Reads all tickets and save out of range values
	for scanner.Scan() {
		out_of_range = append(out_of_range, get_out_of_range(all_ranges, scanner.Text())...)
	}
	log.Println("Out of ranges:", out_of_range)

	sum := 0
	for i := 0; i < len(out_of_range); i++ {
		sum += out_of_range[i]
	}
	log.Println("Sum:", sum)
}
