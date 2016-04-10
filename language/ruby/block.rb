#!/usr/bin/ruby
#
# Experiment with ruby block.


# Ruby Code blocks (called closures in other languages) are chunks of code
# between braces {} or between do-end that you can associate with method
# invocations, almost as if they were parameters. A Ruby block is a way of
# grouping statements, and may appear only in the source adjacent to a method
# call; the block is written starting on the same line as the method call's
# last parameter (or the closing parenthesis of the parameter list). The code
# in the block is not executed at the time it is encountered. Instead, Ruby
# remembers the context in which the block appears (the local variables, the
# current object, and so on) and then enters the method.
#
# The Ruby standard is to use braces for single-line blocks and do-end for
# multi-line blocks. Any method can be called with a block as an implicit
# argument. Inside the method, you can call the block using the yield keyword
# with a value (block argument).
#
# Also, blocks can have their own arguments. There are many methods in Ruby
# that iterate over a range of values. Most of these iterators are written in
# such a way as to be able to take a code block as part of their calling syntax.
# The method can then yield control to the code block (i.e. execute the block)
# during execution as many times as is necessary for the iteration to complete
# (e.g. if we are iterating over array values, we can execute the block as many
# times as there are array values etc.).


# Here, we define a block {puts 'Hello'}. We can think of it as an implicit
# parameter to greet function. Code blocks may appear only in the source adjacent
# to a method call. A naked block can't live in Ruby, this is a compilation error.
#   {puts "hello"}
# The followings are equivalent. Note as mentioned above, it's recommended to
# use do-end block for multi-line blocks.
def greet
  yield
end

greet {puts 'Greet'}
greet() {puts 'Greet'}
greet() {
  puts 'Greet'
}
greet() do
  puts 'Multiple'
  puts 'Greet'
end


# Same applies to function with paramter.
def hello(name)
  puts "Hello #{name}"
  yield
end

hello("World") {puts "Hello World"}
hello("World") {
  puts "Hello World"
}
hello("World") do
  puts 'Multiple'
  puts 'Hello World'
end


# You can provide parameters to the call to yield: these will be passed to the
# block. Within the block, you list the names of the arguments to receive the
# parameters between vertical bars (|).  Also note here we use block_given? to
# decide if a block is given to the function.
def parameters
	puts 'Here, have two random numbers.'
	yield rand(10), rand(50) if block_given?
	puts 'Again.'
	yield(rand(10), rand(50)) if block_given?
	puts 'Now say thank you!'
end
parameters { |x,y| puts "#{x}, #{y}" }


# A code block's return value (like that of a method) is the value of the last
# expression evaluated in the code block. This return value is made available
# inside the method; it comes through as the return value of yield.
def returnvalue
  print "It gives me: ", yield(1, 2), "\n"
end
returnvalue { |x,y| x + y }


# Quite a few builtin methods (esp iterators) use block to operate on data.
presidents = ["Ford", "Carter", "Reagan", "Bush1", "Clinton", "Bush2"]
presidents.each {
	|name|     # This is block argument, contains current array element.
	print "#{name} "
}
print "\n"

10.times do |i|
  print "#{i} "
end
print "\n"

numbers = [1, 2, 5, 6, 9, 21]
numbers.each do |x|
  puts "#{x} is " + (x >= 3 ? "many" : "few")
end

squares = numbers.map {|x| x * x}
print squares, "\n"

my_array = ["alpha", "beta", "gamma"]
my_array.collect do |word|
  puts word.capitalize
end


# Block variables. After the block has executed, i outside the block is the
# original i.
i = -99
puts "Before: " + i.to_s
(1..2).each {
  |i|
  puts i
}
puts "After : " + i.to_s        # i will be -99
# However, for the following code, since x is not a block parameter here, the
# variable x is the same inside and outside the block.
x = 10
5.times do |y|
  x = y
  puts "x inside the block: #{x}"
end
puts "x outside the block: #{x}" # x will be 4


# Example usage from vagrant.
def config_vm_define (vm_name)
  print "Configure vm ", vm_name, "\n"
  yield "Provide a host object to configure."
end

config_vm_define "Host1" do |host|
  puts host
end


# Block & Proc

# Whenever a block is appended to a method call, Ruby automatically converts
# it to a Proc object (block is actually a Proc, see proc.rb), but one without
# an explicit name. The method, however, has a way to access this Proc, by
# means of the yield statement.
def do_twice
  yield                       # 'yield' will call the block passed in.
  yield
end

# {} and do...end are equivalent here.
do_twice {puts "Hola"}
do_twice do puts "HolaHola" end


# The method do_twice is defined and called with an attached block. Although
# the method did not explicitly ask for the block in its arguments list, the
# yield can call the block. This can be implemented in a more explicit way
# using a Proc argument:
def do_twice(what)
  what.call
  what.call
end

do_twice Proc.new {puts "Hola"}


# Blocks are so closely related to Procs that it gives many newbies a
# headache trying to decipher how they actually differ. I will try to
# ease on comprehension with a (hopefully not too corny) metaphor. Blocks,
# as I see them, are unborn Procs. Blocks are the larval, Procs are the
# insects. A block does not live on its own - it prepares the code for
# when it will actually become alive, and only when it is bound and
# converted to a Proc, it starts living.
# A naked block can't live in Ruby, this is a compilation error.
#   {puts "hello"}
# Now it's alive, having been converted to a Proc.
pr = Proc.new {puts "Hello"}
pr.call
