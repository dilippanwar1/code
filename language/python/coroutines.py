def rota(people):
  """rota is a generator; it will never be exhausted.

  Note that we create a list of people, so we isolate the generator with
  the rest of the program changing the list.
  """
  _people = list(people)
  current = 0
  while len(_people):
    yield _people[current]
    current = (current + 1) % len(_people)

def rota_coroutine(people):
  """rota is a coroutine.

  Coroutines are essentially generators which allow you to pass data back
  into the generator function. For example, lets say we are almost happy
  with our rota generator, but we would like a way of updating the internal
  list of people on the rota
  """
  _people = list(people)
  current = 0
  while len(_people):
    command = yield _people[current]
    current = (current + 1) % len(_people)
    if command:
      comm, name = command
    if comm == "add":
      _people.append(name)
    elif comm == "remove" and name in _people:
      _people.remove(name)

def printname(name):
  print "It's %s's turn." % name


if __name__ == "__main__":
  people = ["Ant", "Bernard", "Carly", "Deb", "Englebert"]
  r = rota(people)
  # Change list of people, but won't change iterator.
  people = ["Deyuan", "Sijia", "BabaMama"]
  for i in range(10):
    printname(r.next())

  r = rota_coroutine(people)
