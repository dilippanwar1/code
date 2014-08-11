# Same example, but use real class.


# Remember that `type` is actually a class like `str` and `int`, so you
# can inherit from it.
class UpperAttrMetaclass(type):
  # __new__ is the method called before __init__, it's the method that creates
  # the object and returns it.  While __init__ just initializes the object
  # passed as parameter, you rarely use __new__, except when you want to control
  # how the object is created.  Here the created object is the class, and we
  # want to customize it, so we override __new__.  You can do some stuff in
  # __init__ too if you wish some advanced use involves overriding __call__ as
  # well, but we won't see this.
  # ALL In ALL, we override __new__ to return a class, e.g.. class Foo(), which
  # later used to create object.
  def __new__(cls, clsname, bases, attrs):
    """
    Args:
      cls: Reference to class itself, i.e. <class '__main__.UpperAttrMetaclass'>
      classname: Name of the class to construct. Here, it's Foo.
      bases: The parents of the class to construct, a tuple. Here, it's ().
      attrs: A dictionary of the attributes of the class to construct, including
           those start with '__'. Here, it's {'bar': 'bip', '__module__': '__main__',
           '__metaclass__': <class '__main__.UpperAttrMetaclass'>}
    """
    uppercase_attr = {}
    for name, val in attrs.items():
      if not name.startswith('__'):
        uppercase_attr[name.upper()] = val
      else:
        uppercase_attr[name] = val
    return type.__new__(cls, clsname, bases, uppercase_attr)


class Foo():
  # Normally, when program counter points to the line 'class Foo()', it will
  # create the class Foo in memory and then execute next line (here, the print
  # statement).  Since we have metaclass, python will execute the __new__
  # method in Metaclass before executing print statement.  So we can think of
  # it like Foo = UpperAttrMetaclass.__new__().
  __metaclass__ = UpperAttrMetaclass
  bar = 'bip'


print(hasattr(Foo, 'bar'))      # False
print(hasattr(Foo, 'BAR'))      # True
f = Foo()
print(f.BAR)                    # 'bip'
