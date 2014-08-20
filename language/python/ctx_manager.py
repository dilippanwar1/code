class Openfile:
  def __init__(self, msg):
    self.msg = msg
  def __enter__(self):
    print "enter"
    return self.msg
  def __exit__(self, *args):
    print "exit"


with Openfile('hehe') as w:
  print w











