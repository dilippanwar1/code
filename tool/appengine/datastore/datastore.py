import webapp2
import logging
import datetime

from google.appengine.ext import db


#========================================================================
# Datastore entities
#========================================================================

# Each entity in the Datastore has a key that uniquely identifies it. The key
# consists of the following components:
#   The namespace of the entity, which allows for multitenancy
#   The kind of the entity, which categorizes it for the purpose of Datastore queries
#   An identifier for the individual entity, which can be either:
#     a key name string
#     an integer numeric ID
#   An optional ancestor path locating the entity within the Datastore hierarchy
#
# The entity key is unique across Datastore, which is a hash-like value (hased
# based on value mentioned above). Each datastore entity is of a particular kind,
# in python API, entity kind is determined by model class, e.g. Employee. In
# addition to a kind, each entity has an identifier, assigned when the entity is
# created. Because it is part of the entity's key, the identifier is associated
# permanently with the entity and cannot be changed.
#
# For example, if we create an employee like this:
#   employee = Employee(first_name='Antonio', last_name='Salieri')
# Then employee key, identifier will look like this:
#   Entity Kind: Employee
#   Entity Key:  ag1kZXZ-ZGF0YXN0b3JlchULEghFbXBsb3llZRiAgICAgNC7Cgw
#   ID:          5891733057437696
# Or:
# If the employee is created as:
#   employee = Employee(
#     key_name='asalieri', first_name='Antonio', last_name='Salieri')
# Then employee key, identifier will look like this:
#   Entity Kind: Employee
#   Entity Key:  ag1kZXZ-ZGF0YXN0b3JlchYLEghFbXBsb3llZSIIYXNhbGllcmkM
#   Key Name:    asalieri
#
# Note that using the first constructor will create an employee everytime it is
# executed, whereas the second constructor will always refer to the same entity.

class Employee(db.Model):
  first_name = db.StringProperty()
  last_name = db.StringProperty()
  hire_date = db.DateProperty()
  attended_hr_training = db.BooleanProperty()


# To designate an entity's parent, use the parent argument to the model class
# constructor when creating the child entity. The value of this argument can
# be the parent entity itself or its key; you can get the key by calling the
# parent entity's key() method.
#
# Follow previous example, when saving address like this:
#   address = Address(parent=employee, street='2043 Wightman', city='Pittsburgh')
# Then address key, identifier will look like this (Note we don't use key_name for
# address, but employee has key_name):
#   Entity Kind: Address
#   Entity Key:  ag1kZXZ-ZGF0YXN0b3JlcioLEghFbXBsb3llZSIIYXNhbGllcmkMCxIHQWRkcmVzcxiAgICAgPCLCgw
#   ID:          5681726336532480
#   Parent:      ag1kZXZ-ZGF0YXN0b3JlchYLEghFbXBsb3llZSIIYXNhbGllcmkM
#     (Employee: name=asalieri)

class Address(db.Model):
  street = db.StringProperty()
  city = db.StringProperty()


class Person(db.Model):
  first_name = db.StringProperty()
  last_name = db.StringProperty()
  city = db.StringProperty()
  birth_year = db.IntegerProperty()
  height = db.IntegerProperty()


def create_retrieve():
  # Create an employee with key_name.
  employee = Employee(
    key_name='asalieri',
    first_name='Antonio',
    last_name='Salieri',
    hire_date=datetime.datetime.now().date(),
    attended_hr_training = True)
  # Cannot assign integer.
  # employee.first_name = 100
  employee.put()
  # Create an address with 'employee' as its parent.
  address = Address(
    parent=employee,
    street='2043 Wightman',
    city='Pittsburgh')
  address.put()
  logging.info(employee.key())
  logging.info(address.key())
  # Retrieve employee from datastore (Give its kind and key_name).
  employee_key = db.Key.from_path('Employee', 'asalieri')
  same_employee = db.get(employee_key)
  logging.info(same_employee.first_name + ' ' + same_employee.last_name)


  address2 = Address(
    parent=db.Key.from_path('Employee', 'deyuanyuan'),
    street='2316 Murray',
    city='Pittsburgh')
  address2.put()

  for address in Address.all():
    print address.street
    print address.parent_key().name()

create_retrieve()

# Demonstration, won't work.
def query():
  # all() returns a Query object that represents all entities for the kind
  # corresponding to this model.
  q1 = Person.all()
  # A query's filters set constraints on the:
  # 1. properties
  q1.filter("last_name =", "Smith")
  q1.filter("height <=", max_height)
  q1.order("-height")
  # 2. keys
  q2 = Person.all()
  q2.filter('__key__ >', last_seen_key)
  # 3. ancestors
  q3 = Person.all()
  q3.ancestor(ancestor_key)

  # Query is not executed until results are accessed
  for p in q.run(limit=5):
    print "%s %s, %d inches tall" % (p.first_name, p.last_name, p.height)



#========================================================================
# Handlers
#========================================================================
class MainPage(webapp2.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.write('Hello, World!')


app = webapp2.WSGIApplication([
  ('/', MainPage),
], debug=True)
