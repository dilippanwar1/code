#!/bin/bash
# Shell function Examples

# Function name can contain ":", which is a good way to
# enforce namespace in shell script.
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
