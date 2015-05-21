"""
Download google appengine python sdk and start with:
  $ ~/code/source/google_appengine/dev_appserver.py .
Assume working dir is current directory and sdk is installed in code/source.

Application URL: localhost:8080
Admin Console URL: localhost:8000
"""

import webapp2
import logging
import datetime

import properties

from google.appengine.ext import db


#========================================================================
# Datastore entities
#========================================================================

# Each entity in the Datastore has a key that uniquely identifies it. The key
# consists of the following components:
#   The namespace of the entity, which allows for multitenancy
#   The kind of the entity, which categorizes it for the purpose of Datastore
#     queries
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
# Then address key, identifier will look like this (Note we don't use key_name
# for address, but employee has key_name):
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
  # Create an employee with key_name. Multiple run of the function will
  # only create one entity.
  employee = Employee(
    key_name='asalieri',
    first_name='Antonio',
    last_name='Salieri',
    hire_date=datetime.datetime.now().date(),
    attended_hr_training = True)
  # Cannot assign integer to a string property.
  # employee.first_name = 100
  employee.put()
  employee_key = employee.key()          # 'key' has type db.Key
  # We are creating employee using key_name, so it will have a key name and
  # no id. The key itself is a hash of the information mentioned above.
  logging.info('Employee key: %s' % employee_key)
  logging.info('Employee id: %s' %  employee_key.id())
  logging.info('Employee key name: %s' %  employee_key.name())
  logging.info('Employee key to_path: %s' %  employee_key.to_path())

  # Create an address with 'employee' as its parent. Multiple run of the
  # function will create multiple entities.
  address = Address(
    parent=employee,
    street='2043 Wightman',
    city='Pittsburgh')
  address.put()
  address_key = address.key()
  # We are creating address without key_name, so datastore will allocate
  # an id for the entity.
  logging.info('Address key: %s' % address_key)
  logging.info('Address id: %s' %  address_key.id())
  logging.info('Address key name: %s' %  address_key.name())
  logging.info('Address key to_path: %s' %  address_key.to_path())

  # Create another address for later use, note 'deyuanyuan' doesn't exist.
  address2 = Address(
    parent=db.Key.from_path('Employee', 'deyuanyuan'),
    street='2316 Murray',
    city='Pittsburgh')
  address2.put()

  # Now load entities from datastore, and we have no access to above variables.

  # Retrieve employee from datastore (Give its kind and key_name).
  #   Key.from_path(kind, id_or_name, parent=None, namespace=None)
  employee_key = db.Key.from_path('Employee', 'asalieri')
  same_employee = db.get(employee_key)
  logging.info('Retrieved employee "%s" using key name' % (
    same_employee.first_name + ' ' + same_employee.last_name))

  for address in Address.all():
    logging.info("Address: %s for %s" % (
        address.street, address.parent_key().name()))


def allocate_ids():
  # Create an employee using key name.
  employee = Employee(
    key_name='asalieri',
    first_name='Antonio',
    last_name='Salieri',
    hire_date=datetime.datetime.now().date(),
    attended_hr_training = True)
  employee.put()
  employee_key = employee.key()
  logging.info('Employee key: %s' % employee_key)
  logging.info('Employee id: %s' %  employee_key.id())
  logging.info('Employee key name: %s' %  employee_key.name())
  logging.info('Employee key to_path: %s' %  employee_key.to_path())

  # Now call allocate_ids, these ids will be reserved and will not be used
  # by datastore automatically.
  ids = db.allocate_ids(employee.key(), 10)
  ids_range = range(ids[0], ids[1] + 1)
  logging.info('Allocated IDs: %s' % (ids,))

  # Create an instance using our reserved id.
  one_id = ids[0]
  logging.info('Create entity using ID: %s' % one_id)
  new_key = db.Key.from_path('Employee', one_id)
  new_instance = Employee(key=new_key)
  new_instance.put()
  assert new_instance.key().id() == one_id

  # When creating ones using automatical id, datastore will use other ids.
  another_instance = Employee()
  another_instance.put()
  another_id = another_instance.key().id()
  logging.info('Create entity using automatic id: %s' % another_id)
  assert another_id  not in ids_range


# Demonstration only.
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
# Datastore property
#========================================================================

class Group(db.Model):
  title = db.StringProperty()
  # Represent a group memebers, a map of {'level': 'name'}, where level
  # is one of 'admin', 'normal' and name is a list of string.
  members = properties.JsonProperty(default={'admin': [], 'name': []})


def custom_properties():
  group = Group(
    title='datastore',
    members={'admin': ['deyuan'], 'normal': ['deyuan2', 'deyuan3']})
  group.put()
  group_key = group.key()
  same_group = db.get(group_key)

  group = Group(title='datastore2')
  group.put()
  group_key = group.key()
  same_group = db.get(group_key)
  same_group.members['admin'].append('deyuan')
  print same_group.members



#========================================================================
# Handlers
#========================================================================
class Example1(webapp2.RequestHandler):
  def get(self):
    create_retrieve()
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.write('Hello, World! Example1')


class Example2(webapp2.RequestHandler):
  def get(self):
    allocate_ids()
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.write('Hello, World! Example2')


class Example3(webapp2.RequestHandler):
  def get(self):
    custom_properties()
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.write('Hello, World! Example3')


class DeleteAll(webapp2.RequestHandler):
  def get(self):
    for address in Address.all():
      db.delete(address)
    for employee in Employee.all():
      db.delete(employee)
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.write('Hello, World! DeleteAll')


app = webapp2.WSGIApplication([
  ('/example1', Example1),
  ('/example2', Example2),
  ('/example3', Example3),
  ('/deleteall', DeleteAll),
], debug=True)
