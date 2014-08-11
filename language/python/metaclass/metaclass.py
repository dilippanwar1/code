# Everything is an object in Python. That includes ints, strings, functions
# and classes. All of them are objects. And all of them have been created from
# a class.
# str is the class that creates strings objects; int is the class that creates
# integer objects; type is just the class that creates class objects.

age = 35
print age.__class__             # <type 'int'>

name = 'bob'
print name.__class__            # <type 'str'>

def foo(): pass
print foo.__class__             # <type 'function'>

class Bar(object): pass
b = Bar()
print b.__class__               # <class '__main__.Bar'>

# Now, what is the __class__ of any __class__ ?
print age.__class__.__class__   # <type 'type'>
print name.__class__.__class__  # <type 'type'>
print foo.__class__.__class__   # <type 'type'>
print b.__class__.__class__     # <type 'type'>


# So, a metaclass is just the stuff that creates class objects.
#
# When you do:
#
# class Foo(Bar):
#   pass
#
# Python does the following:
#   Is there a __metaclass__ attribute in Foo?
#   If yes, create in memory a class object (I said a class object, stay with
#     me here), with the name Foo by using what is in __metaclass__.
#   If Python can't find __metaclass__, it will look for a __metaclass__ in
#     Bar (the parent class), and try to do the same.
#   If Python can't find __metaclass__ in any parent, it will look for a
#     __metaclass__ at the MODULE level, and try to do the same.
#   Then if it can't find any __metaclass__ at all, it will use 'type' to create
#     the class object.
#
# Now the big question is, what can you put in __metaclass__ ? The answer is:
# something that can create a class. And what can create a class? type, or
# anything that subclasses or uses it.
#
# See metaclass_example1.py, metaclass_example2.py


# Indeed, metaclasses are especially useful to do black magic, and therefore
# complicated stuff. But by themselves, they are simple:
#   Intercept a class creation
#   Modify the class
#   Return the modified class
