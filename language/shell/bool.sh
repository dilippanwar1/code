#!/bin/bash

the_world_is_flat=true
if [[ "$the_world_is_flat" = true ]] ; then
  echo 'Be careful not to fall off!'
fi

ls xxx || echo "abc"
ls xxx && echo "abc"
