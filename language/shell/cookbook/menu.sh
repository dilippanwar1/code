#!/bin/bash
#
# A simple menu

selection=

until [ "$selection" = "0" ]; do
  echo "
    PROGRAM MENU
    1 - display free disk space
    2 - display free memory

    0 - exit program
"
  echo -n "Enter selection: "
  read selection
  case $selection in
    1 ) df ;;
    2 ) free ;;
    0 ) exit ;;
    * ) echo "Please enter 1, 2, or 0"
  esac
done
