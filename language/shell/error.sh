#!/bin/bash


# Check the exit status.
cd non_exist_dir
if [ "$?" = "0" ]; then
	ls *
else
	echo "Cannot change directory!" 1>&2
fi


# A better way.
if cd non_exist_dir; then
  ls *
else
	echo "Cannot change directory!" 1>&2
fi


# An error exit function.
function error_exit
{
	echo "$1" 1>&2
  # exit 1
}

# Using error_exit
if cd non_exist_dir; then
	ls *
else
	error_exit "Cannot change directory!  Aborting."
fi


# Simplest of all (comment out "ls *" since we are not actually aborting).
cd non_exist_dir || error_exit "Cannot change directory! Aborting"
# ls *


# Another way to do it if exiting is not desired.
cd non_exist_dir && ls *


# A slicker error handling routine.
PROGNAME=$(basename $0)

function better_error_exit
{
  #	----------------------------------------------------------------
  #	Function for exit due to fatal program error
  #		Accepts 1 argument:
  #			string containing descriptive error message
  #	----------------------------------------------------------------
  # The use of the curly braces within the error_exit function is an example
  # of parameter expansion. You can surround a variable name with curly braces
  # (as with ${PROGNAME}) if you need to be sure it is separated from surrounding
  # text. Some people just put them around every variable out of habit. That
  # usage is simply a style thing. The second use, ${1:-"Unknown Error"} means
  # that if parameter 1 ($1) is undefined, substitute the string "Unknown Error"
  # in its place. Using parameter expansion, it is possible to perform a number
  # of useful string manipulations.
	echo "${PROGNAME}: ${1:-"Unknown Error"}" 1>&2
	exit 1
}

# Example call of the error_exit function.  Note the inclusion
# of the LINENO environment variable.  It contains the current
# line number.
echo "Example of error with line number and message"
better_error_exit "$LINENO: An error has occurred."
