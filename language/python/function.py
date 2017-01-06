#!/usr/bin/python

def TestMethodDataParam(data):
  """Data param (int, bool, float, etc) is passed as a 'data'."""
  data = 4

def TestMethodListParam(data, val):
  """List param is passed as a 'reference'."""
  if not isinstance(data, list):
    return
  data.append(val)


if __name__ == '__main__':
  data = 1
  TestMethodDataParam(data)
  print data                    # output: 1

  data = [1, 2, 3]
  TestMethodListParam(data, 4)
  print data                    # output: [1, 2, 3, 4]
