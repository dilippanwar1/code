# Variables are local to function.
def passback
	howIfeel = "good"
	return howIfeel
end

howIfeel = "excellent"
puts howIfeel
mystring = passback
puts howIfeel
puts mystring


# Basic function usage.
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


# Note, if you use "return" within a block, you actually will jump out
# from the function, probably not what you want. To terminate block,
# use break. You can pass a value to break which will be returned as
# the result of the block:
six = (1..10).each {|i| break i if i > 5}
puts six


# Default parameter.
def some_method(value='default', arr=[])
  puts value
  puts arr.length
end

some_method('something')


# The last parameter of a method may be preceded by an asterisk(*), which
# is sometimes called the 'splat' operator. This indicates that more parameters
# may be passed to the function. Those parameters are collected up and an
# array is created.
def calculate_value(x, y, *otherValues)
  print "Other Values: ", otherValues, "\n"
end

calculate_value(1,2,'a','b','c')
# Pack array.
arr = ['a','b','c']
calculate_value(1,2,*arr)


# Another technique that Ruby allows is to give a Hash when invoking a function,
# and that gives you best of all worlds: named parameters, and variable argument
# length.
def accepts_hash(var)
  # 'inspect' will print out what it received
  print "Got: ", var.inspect
  print "\n"
end

# Note the missing parenthesis around the arguments for the accepts_hash function
# call, and notice that there is no { } Hash declaration syntax around the
# :arg1 => '...' code, either.
accepts_hash :arg1 => 'giving arg1', :argN => 'giving argN'
# Equivalent:
#   argument list enclosed in parens
accepts_hash(:arg1 => 'giving arg1', :argN => 'giving argN')
#   hash is explicitly created
accepts_hash({:arg1 => 'giving arg1', :argN => 'giving argN'})


def config_vm_network (type, config)
  puts type
  puts config
end

config_vm_network :shell, guest: 80, host: 8080
