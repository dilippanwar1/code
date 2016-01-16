package main

import (
	"fmt"
	"time"

	"github.com/satori/go.uuid"
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

type Service struct {
	Name           string              `bson:"name,omitempty"`
	ServiceId      string              `bson:"service_id,omitempty"`
	Description    string              `bson:"description,omitempty"`
	ServiceRepoURL string              `bson:"service_repo_url,omitempty"`
	VCS            VersionConrolSystem `bson:"vcs,omitempty`
	BuildPath      string              `bson:"build_path,omitempty"`
}

type VersionConrolSystem string

const (
	Git       VersionConrolSystem = "git"
	Svn       VersionConrolSystem = "svn"
	Mercurial VersionConrolSystem = "mercurial"
)

type Version struct {
	VersionId      string           `bson:"version_id,omitempty"`
	VersionName    string           `bson:"version,omitempty"`
	VersionURI     string           `bson:"version_url,omitempty"`
	CreateTime     time.Time        `bson:"create_time,omitempty"`
	VersionRunInfo []VersionRunInfo `bson:"version_run_info,omitempty"`
}

type VersionRunInfo struct {
	Cluster string `bson:"cluster,omitempty"`
	Project string `bson:"project,omitempty"`
}

type ServiceCollectionManager struct {
	s   *mgo.Session
	col *mgo.Collection
}

func NewServiceCollectionManager(s *mgo.Session) *ServiceCollectionManager {
	return &ServiceCollectionManager{
		s:   s,
		col: s.DB("dev").C("ServiceCollection"),
	}
}

func (m *ServiceCollectionManager) NewServiceDocument(name string) error {
	s := &Service{}
	s.Name = name
	s.ServiceId = uuid.NewV4().String()
	_, err := m.col.Upsert(bson.M{"_id": s.ServiceId}, s)
	return err
}

func (m *ServiceCollectionManager) FindServiceByName(name string) (*Service, error) {
	service := &Service{}
	filter := bson.M{"name": name}
	err := m.col.Find(filter).One(service)
	return service, err
}

func (m *ServiceCollectionManager) FindServiceByVcs(vcs string) ([]Service, error) {
	service := []Service{}
	filter := bson.M{"vcs": vcs}
	err := m.col.Find(filter).Iter().All(&service)
	return service, err
}

func main() {
	session, err := mgo.Dial("localhost")
	if err != nil {
		fmt.Println("Error dailing mongodb")
	}
	defer session.Close()
	session.SetMode(mgo.Strong, true)
	manager := NewServiceCollectionManager(session)

	service, err := manager.FindServiceByName("do-not-exist")
	if err != nil {
		fmt.Println("Trying to find a none exist service and none exist collection:", err)
	}
	fmt.Println("What is the service?", service)

	services, err := manager.FindServiceByVcs("git")
	if err != nil {
		fmt.Println("Trying to find all services from none exist collection:", err)
	}
	fmt.Println("What are the services?", services)

	err = manager.NewServiceDocument("only-a-test")
	if err != nil {
		fmt.Println(err)
	}
}
