package main

type TypeMeta struct {
	Kind       string
	APIVersion string
}

type ListMeta struct {
	SelfLink        string
	ResourceVersion string
}

type ObjectMeta struct {
	Name      string
	Namespace string
}

type Controller struct {
	TypeMeta
	ObjectMeta

	Replica  int
	Selector map[string]string
}

type ControllerList struct {
	TypeMeta
	ListMeta

	Items []Controller
}

func main() {

}
