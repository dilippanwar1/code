#!/bin/python

from functools import partial, wraps

# functools.partial(func[,*args][, **keywords])
#   Return a new partial object which when called will behave like func called
#   with the positional arguments args and keyword arguments keywords. If more
#   arguments are supplied to the call, they are appended to args. If additional
#   keyword arguments are supplied, they extend and override keywords.
#
# functools.partial() is used for partial function application which "freezes"
# some portion of a function's arguments and/or keywords resulting in a new
# object with a simplified signature. E.g. we want to evaluate a math function:
# f(x; a, b, c) = 1000a + 100b + 10c + x
def f(a, b, c, x):
  return 1000*a + 100*b + 10*c + x

# If the parameters are (3, 1, 4), then we can define a parital function:
g = partial(f, 3, 1, 4)
print g(5)                      # 3145


# functools.wraps(wrapped[, assigned][, updated])
#   functools.wraps is typically used with decorator, to fix built-invariables.
#   See http://stackoverflow.com/questions/308999/what-does-functools-wraps-do
#
# @wraps takes 'func', the wrapped function, and return a partial object. The
# partial object is a simple wrap around update_wrapper, where the  wrapped
# parameter is set to 'func'. Then update_wrapper is then called with wrapper
# parameter equals 'decorated'. At last, wrapper is returned. See library
# /usr/lib/python2.7/functools.py
def logger(func):
  @wraps(func)
  def decorated(*args, **kwargs):
    print 'Method called......'
    result = func(*args, **kwargs)
    return result
  return decorated

@logger
def add(a, b):
  """Add two variables."""
  return 'add result is %d' % (a + b)

print add(1,2)
print add.__name__              # add
