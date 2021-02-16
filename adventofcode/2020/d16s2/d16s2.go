package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

// Range contains the maximum and minimum values within a range of numbers.
type Range struct {
	max int
	min int
}

// TicketRange contains zero or more Ranges and a name.
type TicketRange struct {
	ranges []Range
	name   string
}

// Converts a string representation of a TicketRange into a TicketRange struct.
// Errors in converting ascii to int cause a fatal log statement.
func parseTicketRangeString(ticketRangeString string) (ticketRange TicketRange) {
	halves := strings.Split(ticketRangeString, ": ")
	ticketRange.name = halves[0]

	ranges := strings.Split(halves[1], " or ")
	for i := 0; i < len(ranges); i++ {
		var maxAndMin = strings.Split(ranges[i], "-")
		var rangeMin, minError = strconv.Atoi(maxAndMin[0])
		if minError != nil {
			log.Fatal(minError)
		}

		var rangeMax, maxError = strconv.Atoi(maxAndMin[1])
		if maxError != nil {
			log.Fatal(maxError)
		}

		ticketRange.ranges = append(ticketRange.ranges, Range{rangeMax, rangeMin})
	}
	return
}

// Checks whether a value is within at least one of the ranges.
// It returns true if it is at least in one range, false otherwise.
func inRange(ranges []TicketRange, value int) bool {
	for _, ticketRangeValue := range ranges {
		for _, rangeValue := range ticketRangeValue.ranges {
			if value >= rangeValue.min && value <= rangeValue.max {
				return true
			}
		}
	}
	return false
}

// Returns a list of values that are not atleast within one of the ranges.
// ticketString is expected to be 3 comma separated values e.g. "1,2,3".
// Each value of ticketString is processed individually
func getOutOfRange(ranges [][]int, ticketString string) []int {
	var ticketValues = strings.Split(ticketString, ",")
	var outOfRange []int
	for i := 0; i < len(ticketValues); i++ {
		value, err := strconv.Atoi(ticketValues[i])
		if err != nil {
			log.Fatal(err)
		}
		if !inRange(ranges, value) {
			log.Println("Out of range value found:", value)
			outOfRange = append(outOfRange, value)
		}
	}
	return outOfRange
}

func convertTicketString(ticketString string) (ticket []int) {
	valueStrings := strings.Split(ticketString, ",")
	for i := 0; i < len(valueStrings); i++ {
		value, err := strconv.Atoi(valueStrings[i])
		if err != nil {
			log.Fatal(err)
		}
		ticket = append(ticket, value)
	}
	return
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
	var allRanges [][]int

	// Scan() and Text() remove newlines (all spaces?), check for empty string
	for scanner.Text() != "" {
		log.Println("Read:", scanner.Text())
		halves := strings.Split(scanner.Text(), ": ")
		ranges := strings.Split(halves[1], " or ")
		for i := 0; i < len(ranges); i++ {
			var maxAndMin = strings.Split(ranges[i], "-")
			var rangeMin, minError = strconv.Atoi(maxAndMin[0])
			if minError != nil {
				log.Fatal(minError)
			}

			var rangeMax, maxError = strconv.Atoi(maxAndMin[1])
			if maxError != nil {
				log.Fatal(maxError)
			}

			allRanges := append(allRanges, []int{rangeMin, rangeMax})
		}
		scanner.Scan()
	}
	log.Printf("Ranges: %d\n", allRanges)

	scanner.Scan() // Reads "your ticket:"
	scanner.Scan() // Reads the ticket values

	yourTicket := convertTicketString(scanner.Text())
	log.Print("Your ticket:", yourTicket)

	scanner.Scan() // Reads newline
	scanner.Scan() // Reads "nearby tickets:"

	// Reads all tickets and save out of range values
	for scanner.Scan() {
		outOfRange := getOutOfRange(allRanges, scanner.Text())
		if outOfRange != nil {
			continue
		}

	}

}
