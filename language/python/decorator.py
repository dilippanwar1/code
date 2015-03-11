# Experiment with python decorator.

def tags(tag_name):
  # tags will be used as a decorator, e.g. @tags('p') below.  When used, it
  # will be called with a single parameter tag_name='p', at the time when
  # it is defined. tags must return a function: the function's parameter is
  # the function being decorated (here, get_text), and return a decorated
  # version of the function (here, decorator_method). Also at definition time,
  # decorator_method will be called, it should return a method which will
  # be acutally called when user calls get_text.
  def decorator_method(func):
    def func_being_called(name):
      return "<{0}>{1}</{0}>".format(tag_name, name)
    return func_being_called
  return decorator_method

@tags('p')
def get_text(name):
  '''Return some texts that will be shown for user.'''
  return 'Hello ' + name

print get_text('ddysher')       # Returns <p>ddysher</p>


class Module(dict):
  """A dict-like object that can register objects."""

  def Register(self, x, name=None):
    """Register x in a namespace. Can be used as a decorator."""
    if not name:
      name = x.__name__
    self[name] = x
    return x

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
