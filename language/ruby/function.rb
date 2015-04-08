# Experiment with ruby function.


# Followings are three different ways to define a function
def function1
  puts "Hello1"
end

def function2()
  puts "Hello2"
end

def function3 ()
  puts "Hello3"
end

# Note that we can call method without parantheses.
function1
function2
function2()


# Function with parameters. Note this time, we must use function name
# and parameters to call the function, e.g. function4(1,3).
def function4(a, b)
  return a + b
end


# Variables are local to function.
def passback
	howIfeel = "good"
	return howIfeel
end

howIfeel = "excellent"
puts howIfeel                   # => execellent
mystring = passback
puts howIfeel                   # => execellent
puts mystring                   # => good


# Basic function usage with parameters.
def mult(multiplicand, multiplier)
	multiplicand = multiplicand * multiplier
	return multiplicand
end

num1 = 4
num2 = 5
result = mult(num1, num2)
print "num1 is ", num1, "\n"
print "num2 is ", num2, "\n"
print "result is ", result, "\n"


# Default parameter.
def some_method(value='default', arr=[])
  puts value
  puts arr.length
end

# => something
# => 0
some_method('something')
# => default
# => 0
some_method


# The last parameter of a method may be preceded by an asterisk(*), which is
# sometimes called the 'splat' operator. This indicates that more parameters
# may be passed to the function. Those parameters are collected up and an
# array will be created.
def calculate_value(x, y, *otherValues)
  print "Other Values: ", otherValues, "\n"
end

calculate_value(1, 2, 'a', 'b', 'c') # => Other Values: ["a", "b", "c"]
# Defines an array, we use *arr to pack the array.
arr = ['a','b','c']
calculate_value(1, 2, *arr)     # => Other Values: ["a", "b", "c"]


# Note, if you use "return" within a block, you actually will jump out
# from the function, probably not what you want. To terminate block,
# use break. You can pass a value to break which will be returned as
# the result of the block:
six = (1..10).each {|i| break i if i > 5}
puts six


# Another technique that Ruby allows is to give a Hash when invoking a
# function, and that gives you best of all worlds: named parameters, and
# variable argument length.
def accepts_hash(var)
  # 'inspect' will print out what it received
  print "Got: ", var.inspect
  print "\n"
end


# Note the missing parenthesis around the arguments for the accepts_hash
# function call, and notice that there is no { } Hash declaration syntax
# around the :arg1 => '...' code, either.
accepts_hash :arg1 => 'giving arg1', :argN => 'giving argN'
# Equivalent:
#   argument list enclosed in parens
accepts_hash(:arg1 => 'giving arg1', :argN => 'giving argN')
#   hash is explicitly created
accepts_hash({:arg1 => 'giving arg1', :argN => 'giving argN'})


# Example usage from vagrant.
def config_vm_network (type, config)
  puts type
  puts config
end

# => shell
# => {:guest=>80, :host=>8080}
config_vm_network :shell, guest: 80, host: 8080
