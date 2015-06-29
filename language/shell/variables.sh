#!/bin/bash

# There can't be any space between "=" sign. "$title" is called parameter
# expansion.
title="My title"
echo $title
echo ${title}                   # This is preferred over $title
echo "$title"                   # This also works
echo "${title}"
echo "\${title}"                # Need to escape $ if we want to print it

# Common idiom of "-" (hyphen): set a variable iff it's not previously set.
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

# When using 'nounset', we have to test if a variable is set or not using
# [[ -z "${NODE-}" ]], instead of [[ -z "${NODE}" ]].
set -o nounset

if [[ -z "${NODE-}" ]]; then
  echo "ABC"
fi
