# Experiment with ruby class


class Greeter
  attr_accessor :name

  def initialize(name = "World")
    # '@name' is an instance variable, and is available to all the
    # methods of the class.
    @name = name
  end

  def say_hi
    puts "Hi #{@name}!"
  end

  def say_bye
    puts "Bye #{@name}"
  end
end

g = Greeter.new("Pat")
g.say_hi                        # => Hi Pat
g.say_bye                       # => Bye Pat
# We cannot get the name directly, it is hidden away inside the object.
# This will result in a compile error:
# g.@name
# However, since we defined attr_accesssor, it defines two new methods
# for us. 'name' to get the value, and 'name=' to set it.
g.name = "Betty"
g.name
g.say_hi


# Get all methods for Greeter object.
# => [......]
print Greeter.instance_methods, "\n"
# Only get methods defined by us (don't want methods defined by ancestors)
# => [:say_hi, :say_bye, :name, :name=]
print Greeter.instance_methods(false), "\n"
