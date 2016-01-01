#!/bin/bash

ROOT="$(dirname "${BASH_SOURCE}")"
TOTAL_COUNT=5000

cd ${ROOT}/samples
for i in `seq 0 $(($TOTAL_COUNT-1))`; do
  echo "${i}" > ${i}
done
cd -

