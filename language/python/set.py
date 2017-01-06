# Fun facts about Python set.

class Person(object):

  def __init__(self, name, sex, age):
    self.name = name
    self.sex = sex
    self.age = age

  def __eq__(self, other):
    return self.name == other.name

  def __repr__(self):
    return 'An animal named %s' % self.name

  def __hash__(self):
    return hash(repr(self))


if __name__ == '__main__':
  person1 = Person('ABC', 'M', 23)
  person2 = Person('ABC', 'F', 41)

  people = set()
  people.add(person1)

  # The 'in' predicate of set type uses hash value and __eq__ for comparison.
  # General rule:
  #   'Match' if hash(a) == hash(b) and (a is b or a==b) else 'No Match'
  print person1 == person2        # True
  print person1 in people         # True
  print person2 in people         # True

  person1.name = "CBA"
  print person1 in people         # True
