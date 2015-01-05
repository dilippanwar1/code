#!/bin/bash
#
# Experiment with case
#
# The case command has the following form:
# case word in
#     patterns ) commands ;;
# esac
#
# case selectively executes statements if word matches a pattern. You can
# have any number of patterns and statements. Patterns can be literal text
# or wildcards. You can have multiple patterns separated by the "|" character.

echo -n "Enter a number between 1 and 3 inclusive > "
read character
case $character in
  1 ) echo "You entered one."
      ;;
  2 ) echo "You entered two."
      ;;
  3 ) echo "You entered three."
      ;;
  * ) echo "You did not enter a number between 1 and 3."
esac

echo -n "Type a digit or a letter > "
read character
case $character in
  # Check for letters
  [[:lower:]] | [[:upper:]] ) echo "You typed the letter $character"
                              ;;
  # Check for digits
  [0-9] )                     echo "You typed the digit $character"
                              ;;
  # Check for anything else
  * )                         echo "You did not type a letter or a digit"
esac
