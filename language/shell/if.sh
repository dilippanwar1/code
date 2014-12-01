#!/bin/bash
# Shell if flow control

# If statement has the following syntax:
#
#  if commands; then
#    commands
#  elif commands; then
#    commands
#  else
#    commands
#  fi
#
# The elif and else part if optional.  If works by checking the return value
# of its predicate.

if true; then     # true is a simple program that always return 0 code
  echo "This is true"
fi

if true; false; then            # only the last command counts
  echo "This is true"
else
  echo "This is false"
fi

