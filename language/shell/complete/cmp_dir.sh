#!/bin/bash

# cmp_dir - Compare two directories

if [ "$#" -ne 2 ]; then
  echo "usage: $0 directory_1 directory_2" 1>&2
  exit 1
fi

# Make sure both arguments are directories
if [ ! -d "$1" ]; then
  echo "$1 is not a directory!" 1>&2
  exit 1
fi

if [ ! -d "$2" ]; then
  echo "$2 is not a directory!" 1>&2
  exit 1
fi

missing=0
for filename in $1/*; do
  fn="$(basename $filename)"
  if [ -f "$fn" ]; then
    if [ ! -f $2/$fn ]; then
       echo "$fn is missing"
       missing=$((missing + 1))
    fi
  fi
done
echo "$missing files missing"
