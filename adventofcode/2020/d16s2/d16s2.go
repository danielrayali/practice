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
	min int
	max int
}

// TicketRange contains zero or more Ranges and a name.
type TicketRange struct {
	ranges []Range
	name   string
}

func inRange(ticketRange TicketRange, value int) bool {
	for _, currentRange := range ticketRange.ranges {
		if value > currentRange.max || value < currentRange.min {
			return false
		}
	}
	return true
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

		ticketRange.ranges = append(ticketRange.ranges, Range{rangeMin, rangeMax})
	}
	return
}

// Checks whether a value is within at least one of the ranges.
// It returns true if it is at least in one range, false otherwise.
func inAnyRange(ranges []TicketRange, value int) bool {
	for _, ticketRangeValue := range ranges {
		for _, rangeValue := range ticketRangeValue.ranges {
			if value >= rangeValue.min && value <= rangeValue.max {
				return true
			}
		}
	}
	return false
}

// Parses a string representation of a ticket and returns a slice of ints.
// A ticketString is expected to be comma separated list of integers with no spaces.
// String to integer conversion errors cause a fatal log message.
func parseTicketString(ticketString string) (ticket []int) {
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

	scanner := bufio.NewScanner(file)
	scanner.Scan()

	// Contains all ranges specified in the input
	var allRanges []TicketRange
	for scanner.Text() != "" { // Scan() and Text() remove newlines so check for empty string
		log.Println("Read:", scanner.Text())
		allRanges = append(allRanges, parseTicketRangeString(scanner.Text()))
		scanner.Scan()
	}

	scanner.Scan() // Reads "your ticket:"
	scanner.Scan() // Reads the ticket values

	yourTicket := parseTicketString(scanner.Text())
	log.Print("Your ticket:", yourTicket)

	scanner.Scan() // Reads newline
	scanner.Scan() // Reads "nearby tickets:"

	// Setup possible ranges for each column of the ticket entry.
	// This assumes all tickets contain the same number of values.
	possibleRanges := make([][]TicketRange, len(yourTicket))
	for i := 0; i < len(possibleRanges); i++ {
		possibleRanges[i] = make([]TicketRange, len(allRanges))
		if copy(possibleRanges[i], allRanges) != len(allRanges) {
			log.Fatal("All ranges were not copied")
		}
	}

	log.Println("possibleRanges:", possibleRanges)

	for scanner.Scan() {
		nearbyTicket := parseTicketString(scanner.Text())
		for i, ticketValue := range nearbyTicket {
			if !inAnyRange(allRanges, ticketValue) {
				log.Println("Skipping", ticketValue)
				continue
			}

			var newRanges []TicketRange
			for _, remainingRange := range possibleRanges[i] {
				if inRange(remainingRange, ticketValue) {
					newRanges = append(newRanges, remainingRange)
				}
			}

			possibleRanges[i] = make([]TicketRange, len(newRanges))
			copy(possibleRanges[i], newRanges)
		}
	}
	return
}
