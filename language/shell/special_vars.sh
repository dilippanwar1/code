#!/bin/bash

# $0 is the name of the shell script; sometimes used to get directory.
echo $0
# This is somewhat equivalent to $0.
echo ${BASH_SOURCE[0]}
echo $(dirname "${BASH_SOURCE}")

echo $1                         # First param
echo $2                         # Second param
echo "${1}"                     # Also First param

# $! is PID of the most recent background command.
sleep 1 &
echo $!

# pid of the current shell (not subshell)
echo $$

# A string representation of a params; run 'bash special_vars.sh hi ddy.'
# will print: hi ddy.
echo $@
echo "$@"                       # The same as $@
echo ${@:2}

# $# returns the number of parameters
echo $#

# $? is used to find the error code of the last executed command.
ls xxx
echo $?
