# 'type' is a function that lets you know what type an object is, it can also
# create classes on the fly.  'type' can take the description of a class as
# parameters, and return a class.
# 'type' works this way:
#    type(name of the class,
#         tuple of the parent class (for inheritance, can be empty),
#         dictionary containing attributes names and values)


#
# class MyShinyClass(object):
#   pass
#
# Equals:
MyShinyClass = type('MyShinyClass', (), {})
print MyShinyClass
print MyShinyClass()


#
# class Foo(object):
#   bar = True
#
# Equals:
Foo = type('Foo', (), {'bar': True})
print Foo
print Foo.bar
f = Foo()
print f.bar


#
# class FooChild(Foo):
#   pass
#
# Equals:
FooChild = type('FooChild', (Foo,), {})
print FooChild.bar


#
# class FooChild(Foo):
#   def echo_bar(self):
#     print self.bar
#
# Equals:
def echo_bar(self):
  print self.bar

FooChild = type('FooChild', (Foo, ), {'echo_bar': echo_bar})
fooChild = FooChild()
fooChild.echo_bar()
