import itertools


# itertools.chain(*iterables)
# Make an iterator that returns elements from the first iterable until it is
# exhausted, then proceeds to the next iterable, until all of the iterables
# are exhausted. Used for treating consecutive sequences as a single sequence.
def itertoolschain():
  iter1 = set([1, 2, 3])
  iter2 = [4, 5, 6]
  iter3 = {7: '7', 8: '8', 9: '9'}
  # output:
  # 1 2 3 4 5 6 8 9 7 (map is not sorted).
  for value in itertools.chain(iter1, iter2, iter3):
    print value,
  print


# itertools.chain.from_iterable(iterable)
# Alternate constructor for chain(). Gets chained inputs from a single iterable
# argument that is evaluated lazily.
def itertoolsfromiterable():
  iter1 = set([1, 2, 3])
  iter2 = [4, 5, 6]
  iter3 = {7: '7', 8: '8', 9: '9'}
  total = [iter1, iter2, iter3]
  for value in itertools.chain.from_iterable(total):
    print value,
  print


# Cartesian product of input iterables.
def itertoolsproduct():
  iter1 = set([1, 2])
  iter2 = [4, 5]
  iter3 = {7: '7'}
  # output: [(1, 4, 7), (1, 5, 7), (2, 4, 7), (2, 5, 7)]
  print list(itertools.product(iter1, iter2, iter3))


if __name__ == "__main__":
  # itertoolschain()
  # itertoolsfromiterable()
  itertoolsproduct()
