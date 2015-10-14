#!/bin/bash

# Case insensitive compare.
var1="Test"
var2="TEsT"
shopt -s nocasematch
if [[ "${var1}" = "${var2}" ]]; then
  echo ":)"
fi
shopt -u nocasematch
