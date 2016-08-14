#!/usr/bin/python
#
# Run function with retry.

import time
import random

def run_with_rety(func):
  def decorated(*args, **kwargs):
    for i in range(0, 10):
      try:
        return func(*args, **kwargs)
      except BaseException as e:
        print 'Exception %s calling %s' % (str(e), func.__name__)
        time.sleep(1)
        continue
      break
  return decorated


@run_with_rety
def evil_func(name):
  val = random.randint(1, 10)
  print val
  if val < 8:
    raise BaseException("Oh, no")
  else:
    print name + 'Done'

evil_func('abc')
