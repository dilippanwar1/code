#!/usr/bin/python

import warnings

def some_old_function(arg1, arg2):
  warnings.warn(
    "shouldn't use this function anymore! Now use XYZ.",
    RuntimeWarning)
  return arg1 + arg2

print some_old_function(1, 2)
