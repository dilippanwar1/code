#!/bin/bash


# $0 is the name of the shell script; sometimes used to get directory.
echo $0                         # output: special_vars.sh
# This is somewhat equivalent to $0.
echo ${BASH_SOURCE[0]}          # output: special_vars.sh


# $! is PID of the most recent background command.
sleep 1 &
echo $!                         # output: 4359 (PID of sleep 1)

# pid of the current shell (not subshell).
echo $$                         # output: 4358


# A string representation of a params.
# E.g. Run 'bash special_vars.sh Hi, ddysher'
echo $@                         # output: Hi, ddysher
echo ${@:2}                     # output: ddysher


# $# returns the number of parameters
echo $#                         # output: 2


# $? is used to find the error code of the last executed command.
ls xxx
echo $?                         # output: 2 (cannot find file)
