from collections import defaultdict


def Basic():
  s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
  d = defaultdict(list)

  for k, v in s:
    d[k].append(v)

  print d.items()


def Custom():
  # defaultdict has the following signature:
  #   class collections.defaultdict([default_factory[, ...]])
  # Accessing non-exist key on defaultdict will call default_factory to
  # generate the default value
  def default_factory():
    return {'total': 0, 'partial': 0}

  d = defaultdict(default_factory)

  d['comment']['total'] += 1
  print d.items()


if __name__ == '__main__':
  Basic()
  Custom()
