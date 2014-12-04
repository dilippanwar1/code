# Fun facts about Python object.

class Person(object):

  def __init__(self, name, sex, age):
    self.name = name
    self.sex = sex
    self.age = age

  def __eq__(self, other):
    return (self.name == other.name and
            self.sex == other.sex and
            self.age == other.age)

person1 = Person('deyuan', 'M', 10)
person2 = Person('deyuan', 'M', 10)

# By default, object comparison use id() of each object. id() is an integer
# which is guaranteed to be unique and constant for the object during its
# lifetime. Two objects with non-overlapping lifetimes may have the same id
# value. In CPython implementation, this is the address of the object in
# memory. Here, we override __eq__ method, so Python will use this method to
# do object comparison instead of id. Therefore, the output is true; otherwise,
# it's false (using id()).
print person1 == person2        # True


class Animal(object):

  def __init__(self, name, sex, age):
    self.name = name
    self.sex = sex
    self.age = age

  def __repr__(self):
    return 'An animal named %s' % self.name

  # __hash__ is explictly wrote to use name attribute only.
  def __hash__(self):
    return hash(repr(self))

animal1 = Animal('dudu', 'F', 4)
animal2 = Animal('dudu', 'F', 3)

# If no __eq__ is defined while __hash__ is defined, Python will also use
# id() for comparison; therefore, the result is False here.
print animal1 == animal2        # False
