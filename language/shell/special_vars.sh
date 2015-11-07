#!/bin/bash
#
# Special variables in Shell

# $0 is the name of the shell script; sometimes used to get directory.
# ${BASH_SOURCE[0]} is somewhat equivalent to $0.
# Output: special_vars.sh, special_vars.sh .
echo "Shell info:" $0, ${BASH_SOURCE[0]}, $(dirname "${BASH_SOURCE}")

# First param, second param. Two other forms.
echo "Test Params:" $1, $2, ${1}, "${1}"

# $! is PID of the most recent background command.
sleep 1 &
echo "PID of recent backgroud comand:" $! # output: 4359 (PID of sleep 1)

# pid of the current shell (not subshell).
echo "PID of current shell program:" $$ # output: 4358

# A string representation of a params. See param_expansion.sh regarding
# the syntax of the last expression.
# E.g. Run 'bash special_vars.sh Hi ddysher'
# Output: Hi ddysher, Hi ddysher, Hi ddysher, ddysher
echo "String repr of params" $@, ${@}, "$@", ${@:2}

# $# returns the number of parameters (does not include $0)
# E.g. Run 'bash special_vars.sh Hi, ddysher'
echo "Number of params: $#"     # output: 2

# $? is used to find the error code of the last executed command.
ls xxx
echo "Error code:" $?           # output: 1 (cannot find file)

# Show current set of flags.
echo "Current set flag:" $-
