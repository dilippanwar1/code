#!/bin/bash
#
# String in Shell

# Split string with delimiter.
chars="abc,def,xyz"
IFS=',' read -ra char_array <<< "${chars}" # Split into array
for (( i = 0; i < ${#char_array[*]}; i++ )); do
  echo -en "\t${i}: ${char_array[$i]}"
done
echo

# Split string with multiple delimiter.
ssh_info="root:password@43.254.54.58"
IFS=':@' read -ra temp <<< "${ssh_info}"
echo ${temp[0]} ${temp[1]} ${temp[2]}

# Case insensitive compare.
var1="Test"
var2="TEsT"
shopt -s nocasematch
if [[ "${var1}" = "${var2}" ]]; then
  echo ":)"
fi
shopt -u nocasematch
