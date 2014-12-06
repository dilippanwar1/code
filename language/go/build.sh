#!/bin/bash -e
#
# The script overrides GOPATH, which is set to '~/code/source/go-workspace'
# in .zshrc.  Also update PATH to include 'bin' directory.

# Get script full path, no matter where it is called.
BUILD_PATH="$(cd "$(dirname "$0")" && pwd)"

# Export and override GOPATH.
export GOPATH=$BUILD_PATH

# Export PATH, avoid duplicate assignment.
if [[ $PATH != *$BUILD_PATH* ]]; then
  export PATH=$BUILD_PATH/bin:$PATH
fi
