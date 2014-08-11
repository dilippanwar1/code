# Imagine a stupid example, where you decide that all classes in your module
# should have their attributes written in uppercase. There are several ways to
# do this, but one way is to set __metaclass__ at the module level.
#
# This way, all classes of this module will be created using this metaclass, and
# we just have to tell the metaclass to turn all attributes to uppercase.
#
# Luckily, __metaclass__ can actually be any callable, it doesn't need to be a
# formal class (I know, something with 'class' in its name doesn't need to be a
# class, go figure... but it's helpful).

# The metaclass will automatically get passed the same argument that you usually
# pass to `type`.
#
# See metaclass_example2.py for a better version.

def upper_attr(clsname, bases, attrs):
  """
  Return a class object, with the list of its attribute turned into uppercase.
  """
  # Pick up any attribute that doesn't start with '__' and uppercase it.
  uppercase_attr = {}
  for name, val in attrs.items():
    if not name.startswith('__'):
      uppercase_attr[name.upper()] = val
    else:
      uppercase_attr[name] = val

  # Let 'type' do the class creation.
  return type(clsname, bases, uppercase_attr)


# This will affect all classes in the module
__metaclass__ = upper_attr


class Foo():
  # Global __metaclass__ won't work with "object" though, but we can define
  # __metaclass__ here instead to affect only this class and this will work
  # with "object" children.
  bar = 'bip'

print(hasattr(Foo, 'bar'))      # False
print(hasattr(Foo, 'BAR'))      # True
f = Foo()
print(f.BAR)                    # 'bip'
