#!/bin/bash


# $0 is the name of the shell script; sometimes used to get directory.
echo $0
# This is somewhat equivalent to $0.
echo ${BASH_SOURCE[0]}

# $! is PID of the most recent background command.
sleep 1 &
echo $!

# A string representation of a params; run 'bash special_vars.sh hi ddy.'
# will print: hi ddy.
echo $@

# $? is used to find the error code of the last executed command.
ls xxx
echo $?
