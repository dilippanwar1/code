#!/bin/bash
# Shell test command

# The test command is used most often with the if command to perform true/false
# decision. The command is unusual in that it has two different syntactic forms:
# First form:
#  test expression
# Second form:
#  [ expression ]
# The test command works simply. If the given expression is true, test exits
# with a status of zero; otherwise it exits with a status of 1. Note the spaces
# before and after expression are required. For a complete list of expression,
# see "man test".
if [ -f ~/.bash_profile ]; then
    echo "You have a .bash_profile. Things are fine."
else
    echo "Yikes! You have no .bash_profile!"
fi


number=1

# String comparison. Spaces around '=' are required.
if [ "$number" = "1" ]; then
  echo "Number is 1"
fi

# Another string comparison, but this is discouraged.
if [ $number = "1" ]; then
  echo "Number is 1"
fi

# Integer comparison. Spaces around '-eq' are required.
if [ $number -eq 1 ]; then
  echo "Number is 1"
fi
