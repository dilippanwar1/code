#!/bin/bash


# If CONFIG_FILE is empty, then print 'config-default.sh'; if CONFIG_FILE
# is not empty, then print CONFIG_FILE.
echo ${CONFIG_FILE-"config-default.sh"}

API_PORT=${API_PORT:-8080}
echo $API_PORT
