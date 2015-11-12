#!/bin/bash
#
# Shell regular expression

mode="tarballx"
if [[ "${mode}" =~ ^(image|dev|tarball)$ ]]; then
  echo "mode matches"
fi
