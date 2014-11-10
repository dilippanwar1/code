# __getattr__ only gets called for attributes that don't actually exist. If
#  you set the attribute directly, referencing that attribute will retrieve
#  it without calling __getattr__.

# __getattribute__ is called all the times.
#
# Same applies to __setattr__, etc.


print '=================== TestGetAttr ====================================='

class TestGetAttr(object):

  def __init__(self):
    self.attr_a = 'attr_a'

  def __getattr__(self, name):
    print 'Call __getattr__ for %s.' % name
    # object has __getattribute__, __setattr__, doesn't have __setattribute__
    # and __getattr__.
    return None

test_getattr = TestGetAttr()
print 'Value: %s ' % test_getattr.attr_a
print 'Value: %s ' % test_getattr.attr_b


print '=================== TestGetAttribute ================================'

class TestGetAttribute(object):

  def __init__(self):
    self.attr_a = 'attr_a'

  def __getattribute__(self, name):
    print 'Call __getattribute__ for %s.' % name
    return object.__getattribute__(self, name)

test_getattribute = TestGetAttribute()
print 'Value: %s ' % test_getattribute.attr_a  # Call __getattribute__
try:
  print 'Value: %s ' % test_getattribute.attr_b
except AttributeError as e:
  print e


print '============== TestBothGetAttrAndGetAttribute ======================='

class TestBothGetAttrAndGetAttribute(object):

  def __init__(self):
    self.attr_a = 'attr_a'

  def __getattr__(self, name):
    # Called after object.__getattribute__.
    print 'Call __getattr__ for %s.' % name
    return None

  def __getattribute__(self, name):
    print 'Call __getattribute__ for %s.' % name
    return object.__getattribute__(self, name)

test_both = TestBothGetAttrAndGetAttribute()
print 'Value: %s ' % test_both.attr_a
print 'Value: %s ' % test_both.attr_b


print '====================== TestGetSetItem ==============================='

class TestGetSetItem():

  def __init__(self):
    self.items = {}

  def __getitem__(self, key):
    print 'Call __getitem__ for %s.' % key
    return self.items[key]

  def __setitem__(self, key, value):
    self.items[key] = value
    print 'Call __setitem__ for %s.' % key

test_getsetitem = TestGetSetItem()
test_getsetitem['100'] = 100
print test_getsetitem['100']


print '===================== TestGetAttrCall =============================='

class Base():
  def PrintValue(self, value):
    print value

_BASE = Base()

class TestGetAttrCall():

  def __getattr__(self, key):
    if key == 'PrintValue':
      return lambda x: None
    return _BASE.PrintValue


test_getattrcall = TestGetAttrCall()
test_getattrcall.PrintValue(100)
print dir(_BASE)
print dir(test_getattr)
