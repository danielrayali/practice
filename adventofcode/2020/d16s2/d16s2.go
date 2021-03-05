package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

// Range unexported
type Range struct {
	min int
	max int
}

// Field unexported
type Field struct {
	ranges []Range
	name   string
}

// PossibleFields unexported
type PossibleFields struct {
	fields []Field
}

// AllPossibleFields unexported
type AllPossibleFields struct {
	possibleFields []PossibleFields
}

func inAtLeastOneRange(field Field, value int) bool {
	for _, currentRange := range field.ranges {
		if value <= currentRange.max && value >= currentRange.min {
			return true
		}
	}
	return false
}

// func remove(slice []FieldRanges, index int) []FieldRanges {
// 	return append(slice[:index], slice[index+1:]...)
// }

func parseFieldString(fieldString string) (field Field) {
	halves := strings.Split(fieldString, ": ")
	field.name = halves[0]

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

		field.ranges = append(field.ranges, Range{rangeMin, rangeMax})
	}
	return
}

// Checks whether a value is within at least one of the ranges.
// It returns true if it is at least in one range, false otherwise.
func inAnyRange(fields []Field, value int) bool {
	for _, field := range fields {
		for _, rangeValue := range field.ranges {
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
	var possibleFields PossibleFields
	for scanner.Text() != "" { // Scan() and Text() remove newlines so check for empty string
		log.Println("Read:", scanner.Text())
		possibleFields.fields = append(possibleFields.fields, parseFieldString(scanner.Text()))
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
	var allPossibleFields AllPossibleFields
	for i := 0; i < len(possibleFields.fields); i++ {
		allPossibleFields.possibleFields = append(allPossibleFields.possibleFields, possibleFields)
	}
	log.Println("Possible field ranges", allPossibleFields)

	count := 0
	for scanner.Scan() {
		nearbyTicket := parseTicketString(scanner.Text())
		for i, ticketValue := range nearbyTicket {
			if !inAnyRange(possibleFields.fields, ticketValue) {
				count += ticketValue
				continue
			}

			for j, possibleField := range allPossibleFields.possibleFields {
				for k, possibleRange := range possibleField.fields {
					if !inAtLeastOneRange(possibleRange, ticketValue) {
						possibleFields.fields = append(possibleFields.fields[:k], possibleFields.fields[k+1:]...)
						if len(possibleFields.fields) == 1 {
							for l, otherPossibleField := range allPossibleFields.possibleFields {
								if l == j {
									continue
								}
								allPossibleFields.possibleFields[l].fields[]
							}
						}
					}

				}
			}

			for j := 0; j < len(allPossibleFields.possibleFields[j].fields); j++ {
				if !inAtLeastOneRange(allPossibleFields.possibleFields[i].fields[j], ticketValue) {
					log.Println("Removing", possibleFieldRanges[i][j], "because", ticketValue, "is out of range")
					newPossibleFieldRanges = remove(possibleFieldRanges[i], j)
					if len(newPossibleFieldRanges) == 1 {
						for k := 0; k < len(possibleFieldRanges); k++ {
							log.Println("Removing", possibleFieldRanges[i][j].name, "from all other possibles")
							if k == i {
								continue
							}
							possibleFieldRanges[k] = remove(possibleFieldRanges[k], k)
						}
					}
				}
			}
		}
	}
	log.Println("Possible ranges:", possibleFieldRanges)
	log.Println("Scanning error rate:", count)
	return
}
