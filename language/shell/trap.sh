#!/bin/bash

# Program to print a text file with headers and footers.
# Demonstrate shell trap command. The trap command allows you to execute
# a command when a signal is received by your script. It works like this:
#   trap arg signals
# "signals" is a list of signals to intercept and "arg" is a command to
# execute when one of the signals is received.

# Usage: printfile file

# Create a temporary file name that gives preference to the user's local
# tmp directory and has a name that is resistant to "temp race attacks".

if [ -d "~/tmp" ]; then
	TEMP_DIR=~/tmp
else
	TEMP_DIR=/tmp
fi

# To secure temporary file, append printfile with pid and a random num.
TEMP_FILE=$TEMP_DIR/printfile.$$.$RANDOM
PROGNAME=$(basename $0)

function usage {
	# Display usage message on standard error
	echo "Usage: $PROGNAME file" 1>&2
}

function clean_up {
	# Perform program exit housekeeping
	# Optionally accepts an exit status
	rm -f $TEMP_FILE
	exit $1
}

function error_exit {
	# Display error message and exit
	echo "${PROGNAME}: ${1:-"Unknown Error"}" 1>&2
	clean_up 1
}

trap clean_up SIGHUP SIGINT SIGTERM

if [ $# != "1" ]; then
	usage
	error_exit "one file to print must be specified"
fi

if [ ! -f "$1" ]; then
	error_exit "file $1 cannot be read"
fi

pr $1 > $TEMP_FILE || error_exit "cannot format file"

echo -n "Print file? [y/n]: "
read
if [ "$REPLY" = "y" ]; then
	less $TEMP_FILE || error_exit "cannot print file"
fi

clean_up
