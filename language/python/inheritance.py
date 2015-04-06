# Experiment with inheritance in Python.

class ExampleBase(object):

  def MethodA(self):
    print 'In ExampleBase MethodA'

  def MethodB(self):
    print 'In ExampleBase MethodB'


class ExampleChildA(ExampleBase):

  def MethodA(self):
    print 'In ExampleChildA MethodA'


  def MethodB(self):
    print 'In ExampleChildA MethodB'
    self.MethodA()


class ExampleChildB(ExampleChildA):

  def __init__(self, target):
    self._target = target

  def MethodA(self):
    print 'In ExampleChildB MethodA'
    self._target.MethodB()
    self.MethodB()

  def MethodB(self):
    print 'In ExampleChildB MethodB'


def TestCase1():
  childA = ExampleChildA()
  childB = ExampleChildB(childA)
  # Output:
  #  In ExampleChildB MethodA
  #  In ExampleChildA MethodB
  #  In ExampleChildA MethodA
  #  In ExampleChildB MethodB
  childB.MethodA()

TestCase1()


class A(object):
  def __init__(self):
    print 'In A'


class B(object):
  def __init__(self):
    print 'In B'


class C(object):
  def __init__(self):
    print 'In C'
    super(C, self).__init__()


class D(object):
  def __init__(self):
    print 'In D'
    super(D, self).__init__()


class X(A, B):
  """Without calling super, __init__ of A and B won't be called."""
  def __init__(self):
    print 'In X'


class Y(A, B):
  """
  Although Y called super, A doesn't call super, which means B's __init__
  method will not be called.
  """
  def __init__(self):
    print 'In Y'
    super(Y, self).__init__()


class Z(C, D):
  """
  Both C, D and Z called super; therefore, all class's __init__ method
  will be called. Note that C's __init__ will be called bofore D's.
  """
  def __init__(self):
    print 'In Z'
    super(Z, self).__init__()


def TestCase2():
  x = X()                       # In X
  y = Y()                       # In Y; In A
  z = Z()                       # In Z; In C; In D

TestCase2()
