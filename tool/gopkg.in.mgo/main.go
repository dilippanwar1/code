package main

import (
	"fmt"
	"time"

	"github.com/satori/go.uuid"
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

// Service is the management unit in release system.
type Service struct {
	// Service name, e.g. myservice.
	Name string `bson:"name,omitempty"`
	// Service ID that uniquely identifies the service.
	ServiceId string `bson:"service_id,omitempty"`
	// A short, human-readable description of the service.
	Description string `bson:"description,omitempty"`
	// A list of previous version IDs
	PreviousVersions []string `bson:"previous_versions,omitempty"`
	// Repository path of the service, e.g. https://github.com/myrepo/myservice
	ServiceRepoURL string `bson:"service_repo_url,omitempty"`
	// Version control tool.
	VCS VersionConrolSystem `bson:"vcs,omitempty`
	// Build script path.
	BuildPath string `bson:"build_path,omitempty"`
}

type VersionConrolSystem string

const (
	Git       VersionConrolSystem = "git"
	Svn       VersionConrolSystem = "svn"
	Mercurial VersionConrolSystem = "mercurial"
)

// Version associates with a service - a service can have multiple versions.
type Version struct {
	// Version ID that uniquely identifies the version.
	VersionId string `bson:"version_id,omitempty"`
	// The version string, e.g. v1.0.1. Used as docker image tag directly.
	VersionName string `bson:"version,omitempty"`
	// Release version URL, e.g. https://github.com/myrepo/myservice/releases/v1.0
	VersionURI string `bson:"version_url,omitempty"`
	// Time when the version is created.
	CreateTime time.Time `bson:"create_time,omitempty"`
	// If the version is running, shows where it is running.
	VersionRunInfo []VersionRunInfo `bson:"version_run_info,omitempty"`
}

// VersionRunInfo contains information of how is the version deploy, e.g. on
// cluster 'abc', Project 'xyz'.
type VersionRunInfo struct {
	// Which cluster
	Cluster string `bson:"cluster,omitempty"`
	// which project
	Project string `bson:"project,omitempty"`
}

// Define service collection manager.
type ServiceCollectionManager struct {
	s   *mgo.Session
	col *mgo.Collection
}

// NewServiceCollectionManager creates a service collection manager.
func NewServiceCollectionManager(s *mgo.Session) *ServiceCollectionManager {
	return &ServiceCollectionManager{
		s:   s,
		col: s.DB("dev").C("ServiceCollection"),
	}
}

func (m *ServiceCollectionManager) NewServiceCollection(name string) error {
	s := &Service{}
	s.Name = name
	s.ServiceId = uuid.NewV4().String()
	_, err := m.col.Upsert(bson.M{"_id": s.ServiceId}, s)
	return err
}

func main() {
	session, err := mgo.Dial("localhost")
	if err != nil {
		fmt.Println("Error dailing mongodb")
	}
	defer session.Close()
	session.SetMode(mgo.Strong, true)

	manager := NewServiceCollectionManager(session)
	err = manager.NewServiceCollection("OrderSystem")
	if err != nil {
		fmt.Println(err)
	}
}
