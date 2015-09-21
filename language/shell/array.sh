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

# Example
DAOCLOUD_ACCELERATOR="http://47178212.m.daocloud.io,http://dd69bd44.m.daocloud.io,\
  http://9482cd22.m.daocloud.io,http://4a682d3b.m.daocloud.io"
IFS=',' read -ra reg_mirror_arr <<< "${DAOCLOUD_ACCELERATOR}"
reg_mirror=${reg_mirror_arr[$(( ${RANDOM} % ${#reg_mirror_arr[*]} ))]}
echo ${reg_mirror}
