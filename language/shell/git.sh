#!/bin/bash

# Delete all local branches except master and caicloud-master.
for b in `git branch`; do
  if [[ $b != "master" && $b != "caicloud-master" && $b != "*" ]]; then
    git branch -D $b
  fi
done
