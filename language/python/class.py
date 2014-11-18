# Test

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

  def MethodB(self):
    print 'In ExampleChildB MethodB'


childA = ExampleChildA()
childB = ExampleChildB(childA)
childB.MethodA()
