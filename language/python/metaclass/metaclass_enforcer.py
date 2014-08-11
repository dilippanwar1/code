class Field(object):
  """A class that's used to define a class atrribute, enforce its type."""
  def __init__(self, ftype):
    self.ftype = ftype

  def is_valid(self, value):
    return isinstance(value, self.ftype)


class EnforcerMeta(type):
  def __init__(cls, name, bases, ns):
    # store the field definitions on the class as a dictionary
    # mapping the field name to the Field instance.
    cls._fields = {}

    # loop through the namespace looking for Field instances
    for key, value in ns.items():
      if isinstance(value, Field):
        cls._fields[key] = value


class Enforcer(object):
  # Attach the metaclass.
  __metaclass__ = EnforcerMeta

  def __setattr__(self, key, value):
    if key in self._fields:
      if not self._fields[key].is_valid(value):
        raise TypeError('Invalid type for field!')
    super(Enforcer, self).__setattr__(key, value)


class Person(Enforcer):
  name = Field(str)
  age = Field(int)


person = Person()
person.name = 'Deyuan Deng'
person.age = 25

try:
  person.name = 100
except TypeError as e:
  print e
