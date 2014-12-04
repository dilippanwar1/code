#!/bin/bash

# EXIT is built-in. The echo command is executed when shell exits,
# either normally or upon receiving signals.
trap "echo Bye from exit" EXIT

sleep 1
