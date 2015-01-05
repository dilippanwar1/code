#!/bin/bash
#
# Experiment with shell shift command
#
# shift is a shell builtin that operates on the positional parameters. Each
# time you invoke shift, it "shifts" all the positional parameters down by
# one. $2 becomes $1, $3 becomes $2, $4 becomes $3, and so on.

echo "You start with $# positional parameters"

# Loop until all parameters are used up
while [ "$1" != "" ]; do
  echo "Parameter 1 equals $1"
  echo "You now have $# positional parameters"

  # Shift all the parameters down by one
  shift
done
