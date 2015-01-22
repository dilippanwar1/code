#!/bin/bash
#
# Experiment with shell if flow control
#
# If statement has the following syntax:
#
#  if commands; then
#    commands
#  elif commands; then
#    commands
#  else
#    commands
#  fi
#
# Or:
#  if commands
#  then
#    commands
#  elif commands
#  then
#    commands
#  else
#    commands
#  fi
#
# The elif and else part if optional.  If works by checking the return value
# of its predicate.

if true; then     # true is a simple program that always return 0 code
  echo "This is true"
fi

if true
then
  echo "This is another true"
fi

if true; false; then            # only the last command counts
  echo "This is true"
else
  echo "This is false"          # Print false
fi


# The test command is used most often with the if command.
if [ -f ~/.bash_profile ]; then
    echo "You have a .bash_profile. Things are fine."
else
    echo "Yikes! You have no .bash_profile!"
fi
