#!/usr/bin/ruby
#
# Experiment with ruby method.

class Boogy
  def initialize
    @dix = 15
  end

  def arbo
    puts "#{@dix} ha\n"
  end
end

# initializes an instance of Boogy
b = Boogy.new

# method is called on the object, with no arguments
b.arbo

# method/message name is given as a string
b.send("arbo")

# method/message name is given as a symbol
b.send(:arbo)


# Top-level function is actually method of Object.
def say (something)
  puts something
end

say "Hello"
Object.send(:say, "Hello")   # this will be the same as the above line
