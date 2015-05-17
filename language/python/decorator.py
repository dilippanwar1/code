#!/bin/python

# In the simplest term, decorator is a function which takes a function and
# returns decorated function. Below is an example of a logger which records
# calls to the decorated function.
def logger(func):
  # The decorated method is the one that's actually being called.
  def decorated(*args, **kwargs):
    print 'Method call......'
    result = func(*args, **kwargs)
    print 'Method return......'
    return result
  return decorated

@logger
def add(a, b):
  return 'add result is %d' % (a + b)

print add(1,2)
print


# Actually, we can also implement decorator using class with __call__ method.
# The __init__() method will take an argument which is the decorated function.
# The __call__() method is called whenever the decorated function is invoked.
class Logger(object):

  def __init__(self, func):
    print 'In __init__ of Logger'
    self.func = func

  def __call__(self, *args, **kwargs):
    print 'Method call......'
    result = self.func(*args, **kwargs)
    print 'Method return......'
    return result

@Logger
def sub(a, b):
  return 'sub result is %d' % (a - b)

print sub(1, 2)
print


# If decorator needs to take param, then we need three level of functions,
# i.e. one more level than above example.
def tags(tag_name):
  # tags will be used as a decorator, e.g. @tags('p') below.  When used, it
  # will be called with a single parameter tag_name='p', at the time when
  # it is defined. tags must return a function: the function's parameter is
  # the function being decorated (here, get_text), and return a decorated
  # version of the function (here, decorator_method). Also at definition time,
  # decorator_method will be called, it should return a method which will
  # be acutally called when user calls get_text.
  def decorator_method(func):
    def func_being_called(*args, **kwargs):
      return "<{0}>{1}</{0}>".format(tag_name, func(*args, **kwargs))
    return func_being_called
  return decorator_method


@tags('p')
def get_text(name):
  return 'Hello ' + name

print get_text('ddysher')       # Returns <p>Hello ddysher</p>
print


# Use class as decorator, the rule is a little different than above.
class Tags(object):

  def __init__(self, tag_name):
    # NOTE: If there are decorator arguments, the function to be decorated
    # is not passed to the constructor! Only parameter is passed in.
    self.tag_name = tag_name

  def __call__(self, func):
    # If there are decorator arguments, __call__() is only called once, as
    # part of the decoration process! You can only give it a single argument,
    # which is the function object.
    def wrap(*args, **kwargs):
      return "<{0}>{1}</{0}>".format(self.tag_name, func(*args, **kwargs))
    return wrap

@Tags('p')
def get_another_text(name):
  return 'Hello ' + name

print get_another_text('lsj')
print


# Method in a class can also be used as decorator.
class Module(dict):
  """A dict-like object that can register objects."""

  def Register(self, x, name=None):
    """Register x in a namespace. Can be used as a decorator."""
    if not name:
      name = x.__name__
    self[name] = x
    return x

  def GetKnown(self):
    return self

  def __getattr__(self, attr):
    return self[attr]

  def copy(self):
    return self.__class__(self)

module = Module()

@module.Register
class Person(object):
  def __init__(self, name, age):
    self.name = name
    self.age = age

@module.Register
class Vehicle(object):
  def __init__(self, model):
    self.model = model

print module.GetKnown()
