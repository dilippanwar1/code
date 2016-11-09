#!/bin/bash
#
# Clean up all generated files and test images.

for image in `docker images | grep -E "localhost:5000" | awk '{printf "%s:%s\n",$1,$2}'`; do
  docker rmi ${image}
done
