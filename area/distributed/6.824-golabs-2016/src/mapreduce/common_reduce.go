package mapreduce

import (
	"encoding/json"
	"fmt"
	"os"
)

// doReduce does the job of a reduce worker: it reads the intermediate
// key/value pairs (produced by the map phase) for this task, sorts the
// intermediate key/value pairs by key, calls the user-defined reduce function
// (reduceF) for each key, and writes the output to disk.
func doReduce(
	jobName string, // the name of the whole MapReduce job
	reduceTaskNumber int, // which reduce task this is
	nMap int, // the number of map tasks that were run ("M" in the paper)
	reduceF func(key string, values []string) string,
) {
	// Map from reduce key to its values.
	reduceKeyValue := make(map[string][]string)

	// Find reduce task from all map phases, and arrange the values based on key.
	for i := 0; i < nMap; i++ {
		targetFile := reduceName(jobName, i, reduceTaskNumber)
		file, err := os.Open(targetFile)
		if os.IsNotExist(err) {
			// No task from map `i`, continue
			fmt.Printf("doReduce %v no reduce task from %v\n", reduceTaskNumber, targetFile, err)
			continue
		}
		if err != nil {
			// Unexpected error, return early
			fmt.Printf("doReduce %v open file %v error: %v\n", reduceTaskNumber, targetFile, err)
			return // TODO
		}
		defer file.Close()
		enc := json.NewDecoder(file)
		// Arrange values based on key.
		for {
			var data KeyValue
			err = enc.Decode(&data)
			if err != nil {
				break
			}
			if _, ok := reduceKeyValue[data.Key]; !ok {
				reduceKeyValue[data.Key] = []string{}
			}
			reduceKeyValue[data.Key] = append(reduceKeyValue[data.Key], data.Value)
		}
	}

	// Create a file to hold reduce output.
	reduceFilename := mergeName(jobName, reduceTaskNumber)
	file, err := os.Create(reduceFilename)
	if err != nil {
		fmt.Printf("doReduce error create file %v: %v\n", reduceFilename, err)
		return
	}
	fmt.Printf("doReduce created file %v\n", reduceFilename)
	defer file.Close()
	enc := json.NewEncoder(file)

	// Call reduce for each key.
	for k, v := range reduceKeyValue {
		data := reduceF(k, v)
		enc.Encode(KeyValue{Key: k, Value: data})
	}

	// TODO:
	// You will need to write this function.
	// You can find the intermediate file for this reduce task from map task number
	// m using reduceName(jobName, m, reduceTaskNumber).
	// Remember that you've encoded the values in the intermediate files, so you
	// will need to decode them. If you chose to use JSON, you can read out
	// multiple decoded values by creating a decoder, and then repeatedly calling
	// .Decode() on it until Decode() returns an error.
	//
	// You should write the reduced output in as JSON encoded KeyValue
	// objects to a file named mergeName(jobName, reduceTaskNumber). We require
	// you to use JSON here because that is what the merger than combines the
	// output from all the reduce tasks expects. There is nothing "special" about
	// JSON -- it is just the marshalling format we chose to use. It will look
	// something like this:
	//
	// enc := json.NewEncoder(mergeFile)
	// for key in ... {
	// 	enc.Encode(KeyValue{key, reduceF(...)})
	// }
	// file.Close()
}
