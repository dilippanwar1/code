#!/bin/bash -e

# Override go-workspace.
export GOPATH=${PWD}
export PATH=${PWD}/bin:$PATH
