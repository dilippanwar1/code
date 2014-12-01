#!/bin/bash
# Shell function

# A couple of important points about functions. 1. They must appear before you
# attempt to use them; 2. the function body must contain at least one valid
# command (add a return if the function is intend to be empty).
empty_function() {
  return
}
empty_function


# Shell functions cannot return a string directly, you can do:
#  1. echo a string
#  2. return an exit status, which is a number, not a string
#  3. share a variable
# http://stackoverflow.com/questions/8742783/returning-value-from-called-function-in-shell-script
Hello1() {
  echo "Hello World $1 $2"
  echo "Hello Again"
  return 10
}
# The return value is the status code
Hello1 Zara Ali
echo "Return value is $?"       # See special_var.sh
# The "return value" is the echo'd string
ret=$(Hello1 Zara Ali)
echo "Really ${ret}" # Print "Really Hello World Zara Ali\nHello Again"


# You can define a function which would accept parameters while calling those
# function. These parameters would be represented by $1, $2 and so on.
Hello2() {
  echo "Hello World $1 $2"
}
Hello2 Deyuan Deng               # Print "Hello World Deyuan Deng"


# You can also define functions with 'function' keyword, they are equivalent.
# With 'function' keyword, '()' is optional. In general, prefer Hello3 form,
# i.e. include both 'function' and '()'.
function Hello3() {
  echo "Hello World - Hello3"
}
Hello3

function Hello4 {
  echo "Hello World - Hello3"
}
Hello4


# Function name can contain ":", which is a good way to have 'namespace'
# in shell script.
function game::start() {
  echo $0                       # function.sh
  echo $#                       # 0
  echo "Come on"
}
function game::stop() {
  echo $0                       # function.sh
  echo $#                       # 0
  echo "Game over"
}
game::start
game::stop

function short_hash() {
  [[ $# -eq 1 ]] || {
    echo "!!! Internal error.  No data based to short_hash." >&2
    exit 2
  }

  local short_hash
  # ">/dev/null 2>&1" is a common pattern.
  if which md5 >/dev/null 2>&1; then
    short_hash=$(md5 -q -s "$1")
  else
    short_hash=$(echo -n "$1" | md5sum)
  fi

  # Choose the first 5 characters (bash parameter expansion).
  echo ${short_hash:0:5}
}

echo $(short_hash "1234567890")
