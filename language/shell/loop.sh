#!/bin/bash
#
# Experiment with loop flow control

# while loop
number=0
while [ "$number" -lt 10 ]; do
  echo "Number = $number"
  number=$((number + 1))
done

# until loop
number=0
until [ "$number" -ge 10 ]; do
  echo "Number = $number"
  number=$((number + 1))
done

# for loop
# In essence, for assigns a word from the list of words to the specified
# variable, executes the commands, and repeats this over and over until
# all the words have been used up.

# In the example below, the variable i is assigned the string "word1", etc.
for i in word1 word2 word3; do
  echo $i
done

# The interesting thing about for is the many ways you can construct the
# list of words.
count=0
for i in $(cat ~/.bash_history); do
  count=$((count + 1))
  echo "Word $count ($i) contains $(echo -n $i | wc -c) characters"
done

for i in "$@"; do
  echo $i
done

for i in `seq 1 10`; do
  echo $i
done

# Oneliner.
for i in {1..5}; do go run reorder.go; done
