# A minimal experiment with django models/fields.

class ModelMetaclass(type):
  """Mode metaclass that's used to create model."""

  def __new__(cls, clsname, bases, attrs):
    # Convenient reference to type.__new__.
    super_new = super(ModelMetaclass, cls).__new__

    # Ensure initialization is only performed for subclasses of Model
    # (excluding Model class itself).
    parents = [b for b in bases if isinstance(b, ModelMetaclass)]
    if not parents:
      return super_new(cls, clsname, bases, attrs)

    # Create the class (Without any given attributes except __module__).
    module = attrs.pop('__module__')
    new_class = super_new(cls, clsname, bases, {'__module__': module})

    # Keep a record of all declared class attributes, not used though.
    new_class.fields = {}
    for name, val in attrs.items():
      if not name.startswith('__'):
        new_class.fields[name] = val
      # Simply add attribute back to class; in real world, there should be
      # other complex operations.
      setattr(new_class, name, val)

    return new_class


class Model(object):
  """The model class that's supposed to be inherited by real Models."""

  __metaclass__ = ModelMetaclass

  def __init__(self, **kwargs):
    # For this example, self is Person object.
    self.fields = self.fields.copy()
    for name, val in kwargs.items():
      setattr(self, name, val)


class Property(object):
  """A descriptor for property."""

  def __init__(self):
    self._value = self.default_value()

  def __get__(self, obj, obj_type=None):
    return self._value

  def __set__(self, obj, value):
    self.validate_value(value)
    self._value = value


class IntegerProperty(Property):
  """An integer property that only accepts positive number"""

  def default_value(self):
    return 0

  def validate_value(self, value):
    if value < 0:
      raise TypeError('Integer field can only be positive number.')


class StringProperty(Property):
  """A string property that only accepts string whose length is less than 10"""

  def default_value(self):
    return ''

  def validate_value(self, value):
    if len(value) > 10:
      raise TypeError('String field length can only be less than 10.')


# Use cases. Define a model Person, and initilize it.
#
# For this script, the execution sequence is:
# 1. Create ModelMetaclass.
# 2. Create Model by calling ModelMetaclass.__new__(), with params:
#      cls = <class '__main__.ModelMetaclass'>
#      clsname = 'Model'
#      bases = (<type 'object'>,)
#      attrs = {'__return__': {...}, '__module__': '__main__', '__metaclass__': <class '__main__.ModelMetaclass'>, '__doc__': "The model class that's supposed to be inherited by real Models.", '__init__': <function __init__ at 0x7fde6698ba28>}
# 3. Create IntegerProperty and String Property.
# 4. Create Person by calling ModelMetaclass.__new__(), with params:
#      cls = <class '__main__.ModelMetaclass'>
#      clsname = 'Person'
#      bases = (<class '__main__.Model'>,)
#      attrs = {'__return__': {...}, 'age': <__main__.IntegerProperty object at 0x7f148bea66d0>, '__module__': '__main__', 'name': <__main__.StringProperty object at 0x7f148bea6650>}
#    Note that after Person is created by ModelMetaclass, it has a new class
#    variable 'fields', and can be accessed using Person.fields.
# 5. Create person object by calling Model.__init__().
class Person(Model):
  name = StringProperty()
  age = IntegerProperty()


person = Person(name='Deyuan', age=25)
print person.name
person.name = 'Sijia'
print person.name

try:
  person = Person(name='Sijia', age=-25)
  print person.name
except TypeError:
  print 'Cannot assign negative age.'
