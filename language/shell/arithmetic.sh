#!/bin/bash
#
# Experiment with shell arithmetic.

# When you surround an arithmetic expression with the double parentheses,
# the shell will perform arithmetic expansion.
echo $((2 + 2))

first_num=0
second_num=0

echo -n "Enter the first number --> "
read first_num
echo -n "Enter the second number -> "
read second_num

# Note the '$' need not to reference variable, i.e. there is no need to do
# $(($first_num + $second_num))
echo "first number + second number = $((first_num + second_num))"
echo "first number - second number = $((first_num - second_num))"
echo "first number * second number = $((first_num * second_num))"
echo "first number / second number = $((first_num / second_num))"
echo "first number % second number = $((first_num % second_num))"
echo "first number raised to the"
echo "power of the second number   = $((first_num ** second_num))"
