package main

import (
	"expvar"
	"fmt"
	"net/http"
)

func kvfunc(kv expvar.KeyValue) {
	fmt.Println(kv.Key, kv.Value)
}

func main() {
	var innerInt int64 = 10
	pubInt := expvar.NewInt("Int")
	pubInt.Set(innerInt)
	pubInt.Add(2) // Entry: "Int": 12

	var innerFloat float64 = 1.2
	pubFloat := expvar.NewFloat("Float")
	pubFloat.Set(innerFloat)
	pubFloat.Add(0.1) // Entry: "Float": 1.3

	var innerString string = "hello gophers"
	pubString := expvar.NewString("String")
	pubString.Set(innerString) // Entry: "String": "hello gophers"

	pubMap := expvar.NewMap("Map").Init()
	pubMap.Set("Int", pubInt)
	pubMap.Set("Float", pubFloat)
	pubMap.Set("String", pubString)
	pubMap.Add("Int", 1) // Note: this will change "Int" to "Int": 13
	pubMap.Add("NewInt", 123)
	pubMap.AddFloat("Float", 0.5)
	pubMap.AddFloat("NewFloat", 0.9)
	pubMap.Do(kvfunc)

	expvar.Do(kvfunc)

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprint(w, "hello gophers")
	})
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		panic(err)
	}
}
