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
echo "Length of array: ${#LOVES[@]}"          # output: 3
echo "Length of second element: ${#LOVES[1]}" # output: 4

# Loop through array
echo "Loop through array:"
for i in "${LOVES[@]}"
do
  echo -ne "\t${i}"
done
echo

# Append to array in a loop.
args=()
for i in "abc abc xyz"; do
  args+=("$i")
done
for each in "${args[@]}"; do echo "$each"; done

# Print arguments. As shown in special_vars, $@ returns script argument as string.
args="$@"
args_length="${#args[*]}"
echo "Arguments: ${args[0]}, ${args[*]}, ${args_length}"

# Example: randomly choose one item from array.
numbers="1897329,28943,37810,498893"
IFS=',' read -ra number_array <<< "${numbers}"
number=${number_array[$(( ${RANDOM} % ${#number_array[*]} ))]}
echo ${number}

# Example: find executable from predefined location.
locations=("/usr/bin/kubectl" "/usr/local/bin/kubectl" "/opt/bin/kubectl")
for location in ${locations[@]}; do
  if [[ -x ${location} ]]; then
    KUBECTL_PATH=${location}
    break
  fi
done

if [[ ${KUBECTL_PATH} == "" ]]; then
  if [[ -x `which kubectl` ]]; then
    export KUBECTL_PATH=`which kubectl`
  fi
fi

echo $KUBECTL_PATH
