#!/bin/bash
#
# Misc shell builtin functions


# Execute a command with parameter.
function exec-command {
  eval "${1}"
}

# eval will take a command as well as its parameters.
exec-command "touch abc && echo 'Done' && rm -rf abc"
