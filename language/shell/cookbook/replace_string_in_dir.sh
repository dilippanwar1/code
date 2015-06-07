#!/bin/bash

# Replace string in a folder, recursively.
grep -rl 'windows' . | xargs sed -i 's/windows/linux/g'
