#!/bin/bash
#
# Shell 'set' is a command to set or unset values of shell options and
# positional parameters. Using + rather than - causes these flags to be
# turned off.
# http://linuxcommand.org/lc3_man_pages/seth.html

# It is possible to have bash show you what it is doing when you run your
# script. To do this, add a "-x" to the first line of your script. Or use
# set -x to turn tracing on, and set +x to trun tracing off.
number=1
set -x
if [ "$number" = "1" ]; then
  echo "Number equals 1"
else
  echo "Number does not equal 1"
fi
set +x
if [ "$number" = "2" ]; then
  echo "Number equals 1"
else
  echo "Number does not equal 1"
fi
set -x
echo $-                         # Show current set of flags
