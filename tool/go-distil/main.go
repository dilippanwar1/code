package main

import (
	"fmt"

	"github.com/mattevans/distil"
)

func main() {
	data := []map[string]interface{}{
		{"location": "New York", "department": "Engineering", "salary": 120000, "start_date": "2016-01-23T12:00:00Z"},
		{"location": "New York", "department": "Engineering", "salary": 80000, "start_date": "2016-03-23T12:00:00Z"},
		{"location": "New York", "department": "Marketing", "salary": 90000, "start_date": "2016-01-23T12:00:00Z"},
		{"location": "New York", "department": "Marketing", "salary": 150000, "start_date": "2016-01-23T12:00:00Z"},
		{"location": "Chicago", "department": "Engineering", "salary": 120000, "start_date": "2016-01-23T12:00:00Z"},
		{"location": "Chicago", "department": "Engineering", "salary": 160000, "start_date": "2016-03-23T12:00:00Z"},
	}

	// Init distil dataset.
	dataset := distil.NewDataset(data...)

	// Build a distil query and apply filters.
	query := &distil.Query{}
	query.Filters = append(query.Filters, distil.Filter{
		Field: "location",
		Value: "Chicago",
		Operator: distil.Operator{
			Code: "eq",
			Type: "string",
		},
	})

	// Run it.
	results, err := dataset.Run(query)
	if err != nil {
		fmt.Errorf("Unexpected error running query: %s", err.Error())
	} else {
		fmt.Printf("%+v\n", results)
	}
}
