package rest

import (
	"fmt"

	// "github.com/ddysher/packages/api"
)

func CreateService() {
	service := Service{}
	service.Name = "Deyuan"
	fmt.Printf("%+#v\n", service)
}
