#!/bin/bash

pids=""

function doSleep {
  sleep 5
  if [[ "$1" == "9" ]]; then
    sleep 15
    echo "I'm bad, but I'm done: $1"
  else
    echo "I'm done: $1"
  fi
}

for i in `seq 0 9`; do
  doSleep $i &
  pids="$pids $!"
done


echo "I'm waiting..."
echo $pids

# It's important to note that the syntax is exactly 'wait $pids', using
# 'wait "$pids"' will result in wrong pid spec.
wait $pids

echo "All Done!"
