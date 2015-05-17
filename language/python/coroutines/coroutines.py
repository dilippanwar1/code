# When the logic for a function with complex behavior is divided into several
# self-contained steps that are themselves functions, these functions are called
# helper functions or subroutines. Subroutines are called by a main function
# that is responsible for coordinating the use of several subroutines.
#
# There is a different way of decomposing complex computations using coroutines,
# an approach that is particularly applicable to the task of processing sequential
# data. Like a subroutine, a coroutine computes a single step of a complex
# computation. However, when using coroutines, there is no main function to
# coordinate results. Instead coroutines themselves link together to form a
# pipeline. There may be a coroutine for consuming the incoming data and sending
# it to other coroutines. There may be coroutines that each do simple processing
# steps on data sent to them, and there may finally be another coroutine that
# outputs a final result.
#
# http://wla.berkeley.edu/~cs61a/fa11/lectures/streams.html#coroutines


# Example

def rota_generator(people):
  """rota is a generator; it will never be exhausted.

  Note that we create a list of people, so we isolate the generator with
  the rest of the program changing the list.
  """
  _people = list(people)
  current = 0
  while len(_people):
    yield _people[current]
    current = (current + 1) % len(_people)

if __name__ == "__main__":
  people = ["Ant", "Bernard", "Carly", "Deb", "Englebert"]
  r = rota_generator(people)
  for i in range(10):
    print "It's %s's turn." % r.next()


def rota_coroutine(people):
  """rota is a coroutine.

  Coroutines are essentially generators which allow you to pass data back
  into the generator function. For example, let's say we are almost happy
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
  r = rota_coroutine(people)

  for i in range(6):
    printname(r.next())
  printname(r.send(("add", "Fred")))

  for i in range(7):
    printname(r.next())
  printname(r.send(("remove","Deb")))

  for i in range(6):
    printname(r.next())
