#!/bin/bash
#
# Shell regular expression

mode="tarballx"
if [[ "${mode}" =~ ^(image|dev|tarball)$ ]]; then
  echo "mode matches"
fi

if [[ $1 =~ ^v[0-9]+\.[0-9]+\.[0-9]+$ && ! $1 =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}$ ]]; then
  echo "timestamp"
fi

for image in `docker images | grep -E "caicloud/(cds-executor|cds-validator|cds-server)" | awk '{printf "%s:%s\n",$1,$2}'`; do
  docker rmi ${image}
done
