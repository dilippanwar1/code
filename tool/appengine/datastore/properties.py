# Document
# https://cloud.google.com/appengine/docs/python/datastore/propertyclass

import copy
import json
from google.appengine.ext import db


class JsonProperty(db.TextProperty):
  """A database property to hold json object."""

  def __init__(self, **kwargs):
    kwargs.setdefault('default', {})
    super(JsonProperty, self).__init__(**kwargs)

  def default_value(self):
    """The default value should be a copy to avoid sharing between instances.

    The method is called when creating model instance without default value.
    This one will not call default_value():
      group = Group(title='datastore', members={'admin': ['deyuan'], 'normal': ['deyuan2', 'deyuan3']})
    This one will:
      group = Group(title='datastore')
    """
    return copy.deepcopy(self.default)

  def get_value_for_datastore(self, instance):
    """Dump data for datastore storage, dictionary to string.

    The method is called prior to storing the model instance, e.g. calling put.
    Value returned from the method will be stored in datastore. In this case,
    it converts the property value from a python dictionary to string.
    """
    value = getattr(instance, self.name)
    if value is None:
      return None
    return db.Text(json.dumps(value))

  def make_value_from_datastore(self, value):
    """Load data saved in datastore, string to dictionary.

    The method is called prior to retrieving model instance, e.g. calling get.
    It returns the Python-native representation for the given value from the
    datastore. In this case, property value is converted from string to python
    dictionary.
    """
    if value is None:
      return None
    return json.loads(value)

  def validate(self, value):
    """Validate property.

    The method is called on both instance save and get."""
    try:
      json.dumps(value)
    except TypeError as e:
      raise db.BadValueError('Value is not json serializable (type=%r): %s' % (
          type(value), e))
    return value

  # The following two methods are used to support Django form in datastore.

  def get_value_for_form(self, instance):
    """Extract the property value from the instance for use in a form."""
    return getattr(instance, self.name)

  def make_value_from_form(self, value):
    """Convert a form value to a property value."""
    return value
