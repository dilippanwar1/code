"""Experiment with Python Mock Library.

For Python < 3.3, install the library using:
  pip install -U mock
"""

from mock import patch Mock

class Person(object):
  """A simple test class."""
  def __init__(self, name, age):
    self.name = name
    self.age = age

  def isYouth(self):
    return self.age <= 25
