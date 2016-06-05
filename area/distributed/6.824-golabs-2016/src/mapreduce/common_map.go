package mapreduce

import (
	"encoding/json"
	"fmt"
	"hash/fnv"
	"io/ioutil"
	"os"
)

// doMap does the job of a map worker: it reads one of the input files
// (inFile), calls the user-defined map function (mapF) for that file's
// contents, and partitions the output into nReduce intermediate files.
func doMap(
	jobName string, // the name of the MapReduce job
	mapTaskNumber int, // which map task this is
	inFile string,
	nReduce int, // the number of reduce task that will be run ("R" in the paper)
	mapF func(file string, contents string) []KeyValue,
) {
	// Read the file content and call map function with the content.
	bytes, err := ioutil.ReadFile(inFile)
	if err != nil {
		fmt.Printf("doMap error open file %v for read: %v\n", inFile, err)
		return
	}
	mapResult := mapF(inFile, string(bytes))

	// Create 'nReduce' number of files, and make them json encoders. The
	// intermediate file is multiple lines of json encoded data, each line
	// is a key/value pair.
	encoders := []*json.Encoder{}
	for i := 0; i < nReduce; i++ {
		reduceFilename := reduceName(jobName, mapTaskNumber, i)
		file, err := os.Create(reduceFilename)
		if err != nil {
			fmt.Printf("doMap error create file %v: %v\n", reduceFilename, err)
			return
		}
		fmt.Printf("doMap created file %v\n", reduceFilename)
		defer file.Close()
		encoders = append(encoders, json.NewEncoder(file))
	}

	// Find the file (encoder) the key belongs to and write it to the file.
	// The file also means reduce task, so this is also where the map associates
	// task with reduce task.
	for i := 0; i < len(mapResult); i++ {
		keyValue := mapResult[i]
		enc := encoders[ihash(keyValue.Key)%uint32(nReduce)]
		enc.Encode(keyValue)
	}

	// TODO:
	// You will need to write this function.
	// You can find the filename for this map task's input to reduce task number
	// r using reduceName(jobName, mapTaskNumber, r). The ihash function (given
	// below doMap) should be used to decide which file a given key belongs into.
	//
	// The intermediate output of a map task is stored in the file
	// system as multiple files whose name indicates which map task produced
	// them, as well as which reduce task they are for. Coming up with a
	// scheme for how to store the key/value pairs on disk can be tricky,
	// especially when taking into account that both keys and values could
	// contain newlines, quotes, and any other character you can think of.
	//
	// One format often used for serializing data to a byte stream that the
	// other end can correctly reconstruct is JSON. You are not required to
	// use JSON, but as the output of the reduce tasks *must* be JSON,
	// familiarizing yourself with it here may prove useful. You can write
	// out a data structure as a JSON string to a file using the commented
	// code below. The corresponding decoding functions can be found in
	// common_reduce.go.
	//
	//   enc := json.NewEncoder(file)
	//   for _, kv := ... {
	//     err := enc.Encode(&kv)
	//
	// Remember to close the file after you have written all the values!
}

func ihash(s string) uint32 {
	h := fnv.New32a()
	h.Write([]byte(s))
	return h.Sum32()
}