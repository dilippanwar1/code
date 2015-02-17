#!/bin/bash
#
# Arrays in Shell
# http://www.thegeekstuff.com/2010/06/bash-array-tutorial/

# Array basics
NAME[0]="Zara"
NAME[1]="Qadir"
NAME[2]="Mahnaz"
NAME[3]="Ayan"
NAME[4]="Daisy"
echo "First Index: ${NAME[0]}"
echo "Second Index: ${NAME[1]}"
# Use @ or * to print all elements
echo "All Elements: ${NAME[@]}; Another form: ${NAME[*]}"

# Initialize an array during declaration
LOVES=("Mama" "Baba" "Baobao")
echo "${LOVES[@]}"
echo "Length of second element: ${#LOVES[1]}" # output: 4

# Loop through array
echo "Loop through array:"
for i in "${LOVES[@]}"
do
  echo -e "\t${i}"
done

# Print arguments
args=("$@")
args_length=${#args[*]}
echo "${args[0]}, ${args[@]}, ${args_length}"
