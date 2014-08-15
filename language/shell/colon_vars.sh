#!/bin/bash

# Demonstrate the subtle difference between ${var-word} and ${var:-word}
# =================================
# Conclusion
# – The colon (:) construct works when a variable is empty AND unset
# – The non-colon construct only works when the variable is unset
#
# http://wuhrr.wordpress.com/2008/12/08/bash-shell-scripting-a-colon-difference/

clear

printf "\n=================================\n"
printf "\${varName+word} and \${varName:+word} comparison\n\n"

varName="Aloha"
echo "varName is not empty: the two constructs behave the same"
echo " \${varName+Hello World}=${varName+Hello World}"
echo " \${varName:+Hello World}=${varName:+Hello World}"
echo ""

unset varName
echo "varName is unset: they still behave the same way"
echo " \${varName+Hello World}=${varName+Hello World}"
echo " \${varName:+Hello World}=${varName:+Hello World}"
echo ""

varName=""
echo "varName is empty: this is where the two differs"
echo " \${varName+Hello World}=${varName+Hello World}"
echo " \${varName:+Hello World}=${varName:+Hello World}"
echo ""

printf "\n=================================\n"
printf "\${varName-word} and \${varName:-word} comparison\n\n"

varName="Aloha"
echo "varName is not empty: the two constructs behave the same"
echo " \${varName-Hello World}=${varName-Hello World}"
echo " \${varName:-Hello World}=${varName:-Hello World}"
echo ""

unset varName
echo "varName is unset: they still behave the same way"
echo " \${varName-Hello World}=${varName-Hello World}"
echo " \${varName:-Hello World}=${varName:-Hello World}"
echo ""

varName=""
echo "varName is empty: this is where the two differs"
echo " \${varName-Hello World}=${varName-Hello World}"
echo " \${varName:-Hello World}=${varName:-Hello World}"
echo ""
