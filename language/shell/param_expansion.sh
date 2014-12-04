#!/bin/bash
# Shell parameter expansion

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
