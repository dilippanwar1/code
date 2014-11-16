#!/bin/bash

# If CONFIG_FILE is empty, then print 'config-default.sh';
# if CONFIG_FILE is not empty, then print CONFIG_FILE.
echo ${CONFIG_FILE-"config-default.sh"}

# Same as above.
API_PORT=${API_PORT:-8080}
echo $API_PORT

# RANDOM is shell variable that returns a random number.
echo $RANDOM

# PWD is shell variable that returns a current working directory.
echo $PWD
echo $(pwd)

# EXIT is built-in. The echo command is executed when shell exits,
# either normally or upon receiving signals.
trap "echo Bye from exit" EXIT

sleep 1
