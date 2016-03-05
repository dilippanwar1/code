#!/bin/bash
#
# Process management in Shell

# kill all of subprocess on interrupt
trap '{ pkill -P $$; wait; exit 130; }' SIGINT
