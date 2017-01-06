#!/usr/bin/python

def outer(x):
  adjust = -1
  def inner():
    print x + adjust
  return inner

def TestValueScope():
  value = 100

  def valuePrinter():
    print value

  valuePrinter()
  value = 200
  valuePrinter()


if __name__ == '__main__':
  foo = outer(1)
  foo()                         # This actually calls is 'inner()'.
  print foo.func_closure
  TestValueScope()

