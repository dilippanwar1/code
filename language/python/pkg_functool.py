# Experiment with functools module.

# functools.partial(func[,*args][, **keywords])
#   Return a new partial object which when called will behave like func called
#   with the positional arguments args and keyword arguments keywords. If more
#   arguments are supplied to the call, they are appended to args. If additional
#   keyword arguments are supplied, they extend and override keywords. Roughly
#   equivalent to:

def partial_equivalent(func, *args, **keywords):
  def newfunc(*fargs, **fkeywords):
    # All the new function does is combine current parameters with closure
    # parameters, and then call original function.
    newkeywords = keywords.copy()
    newkeywords.update(fkeywords)
    return func(*(args + fargs), **newkeywords)
  # Not strictly needed for partial equivalent to work.
  newfunc.func = func
  newfunc.args = args
  newfunc.keywords = keywords
  return newfunc

# The partial() is used for partial function application which "freezes" some
# portion of a function's arguments and/or keywords resulting in a new object
# with a simplified signature. For example, partial() can be used to create a
# callable that behaves like the int() function where the base argument defaults
# to two:

from functools import partial

basetwo = partial(int, base=2)
basetwo.__doc__ = 'Convert base 2 string to an int.'
print basetwo('10010')          # 18


def get_name(first_name, last_name):
  return '%s %s' % (first_name, last_name)
deng_family = partial_equivalent(get_name, last_name='Deng')
print deng_family('Deyuan')
