import time
from multiprocessing import Process


def AsyncFunc(data):
  time.sleep(2)
  print data
  print 'Bye bye from AsyncFunc'


if __name__ == '__main__':
  p = Process(target=AsyncFunc, args=('Here I am...',))
  p.start()
  print "I'm waiting..."
  p.join()
  print 'Bye bye from main'
