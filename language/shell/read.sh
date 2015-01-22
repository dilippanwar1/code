#!/bin/bash
#
# Experiment with read command.

echo -n "Enter some text > "
# We invoke the read command with "text" as its argument. What this does is
# wait for the user to type something followed by a carriage return (the Enter
# key) and then assign whatever was typed to the variable text.
read text
echo "You entered: $text"

echo -n "Enter some text again > "
# If you don't give the read command the name of a variable to assign its
# input, it will use the environment variable REPLY.
read
echo "You entered: $REPLY"

echo -n "Enter your password > "
# -s will not display user input.
read -s password
echo
echo "You entered: $password"
