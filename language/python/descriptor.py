# Descriptor Protocol
#   descr.__get__(self, obj, type=None) --> value
#   descr.__set__(self, obj, value) --> None
#   descr.__delete__(self, obj) --> None
# That is all there is to it. Define any of these methods and an object is
# considered a descriptor and can override default behavior upon being looked
# up as an attribute.
#
# Invoking Descriptors
# A descriptor can be called directly by its method name. For example,
# d.__get__(obj). Alternatively, it is more common for a descriptor to be
# invoked automatically upon attribute access. For example, obj.d looks up d in
# the dictionary of obj. If d defines the method __get__(), then d.__get__(obj)
# is invoked according to the precedence rules listed below.
#
# The details of invocation depend on whether obj is an object or a class. Either
# way, descriptors only work for new style objects and classes.
#
# ***
# For objects, the machinery is in object.__getattribute__() which transforms b.x
# into type(b).__dict__['x'].__get__(b, type(b)). The implementation works through
# a precedence chain that gives data descriptors priority over instance variables,
# instance variables priority over non-data descriptors, and assigns lowest priority
# to __getattr__() if provided.
#
# For classes, the machinery is in type.__getattribute__() which transforms B.x
# into B.__dict__['x'].__get__(None, B). In pure Python, it looks like:
# ***

def __getattribute__(self, key):
  "Emulate type_getattro() in Objects/typeobject.c"
  v = object.__getattribute__(self, key)
  if hasattr(v, '__get__'):
    return v.__get__(None, self)
  return v


# Example

class RevealAccess(object):
  """
  A data descriptor that sets and returns values normally and prints a message
  logging their access.
  """

  def __init__(self, initval=None, name='var'):
    self.val = initval
    self.name = name

  def __get__(self, obj, objtype):
    print 'Retrieving', self.name
    return self.val

  def __set__(self, obj, val):
    print 'Updating', self.name
    self.val = val


class MyClass(object):
  x = RevealAccess(10, 'var "x"')
  y = 5

m = MyClass()

print m.x
# Retrieving var "x",
# 10

m.x = 20
# Updating var "x"

print m.x
# Retrieving var "x"
# 20

print m.y
# 5
