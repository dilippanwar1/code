import time
from contextlib import contextmanager


class Openfile:
  """
  Define a class with methods '__enter__' and '__exit__' for
  it to be a context manager.
  """
  def __init__(self, msg):
    self.msg = msg

  def __enter__(self):
    print 'enter'
    return self.msg

  def __exit__(self, *args):
    print 'exit'

with Openfile('Nothing') as w:
  print w


@contextmanager
def TimeOp(para=None):
  """A method that logs the time spend on an operation."""
  print 'Start operations'
  start = time.clock()
  # Use tyr...except...finally to trap unhandled error.
  try:
    yield
    success = True
  except:
    success = False
  finally:
    elapsed = time.clock() - start
    print 'Something passed in: %s' % para
    print 'Operation finished %s' % ('successfully' if success else 'with error')

def UseTimeOp():
  with TimeOp('Sleep 2 secs'):
    time.sleep(2)

def UseTimeOpWithException():
  with TimeOp('Raise exception'):
    raise Exception('Something went wrong')


UseTimeOp()
UseTimeOpWithException()
