#!/usr/bin/python

def div(val1, val2):
  assert val2 != 0
  return val1 / val2

def test():
  assert 1==2, 'Not equal'
  assert 1==3, 'Not equal'

if __name__ == '__main__':
  # print div(2, 1)
  # print div(2, 0)
  test()
