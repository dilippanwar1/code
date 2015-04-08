# Experiment with ruby block.


# The block argument (name) contains the current array element, and everything
# else until the closing brace contains code to operate on the block argument.
# The block argument is always enclosed in vertical lines (pipe symbols).
presidents = ["Ford", "Carter", "Reagan", "Bush1", "Clinton", "Bush2"]
presidents.each {
	|name|      # This is block argument, contains current array element.
	puts name
}


# You can also define it by enclosing it in a do and an end, where the do
# replaces the opening brace, and the end replaces the closing brace.
presidents.each do |name|
	puts name
end


# Use a global variable.
i = -99
puts "Before: " + i.to_s
(1..10).each {
  |i|
  puts i
}
puts "After : " + i.to_s


my_array = ["alpha", "beta", "gamma"]
puts my_array.collect {
	|word|
	word.capitalize
}
puts "======================"
puts my_array.collect do
	|word|
	word.capitalize
end


# Blocks are so closely related to Procs that it gives many newbies a
# headache trying to decipher how they actually differ. I will try to
# ease on comprehension with a (hopefully not too corny) metaphor. Blocks,
# as I see them, are unborn Procs. Blocks are the larval, Procs are the
# insects. A block does not live on its own - it prepares the code for
# when it will actually become alive, and only when it is bound and
# converted to a Proc, it starts living.

# A naked block can't live in Ruby, this is a compilation error.
# {puts "hello"}

# Now it's alive, having been converted to a Proc.
pr = lambda {puts "Hello"}
pr.call


# Passing a block to a method, examples:
10.times do |i|
  print "#{i} "
end

numbers = [1, 2, 5, 6, 9, 21]

numbers.each do |x|
  puts "#{x} is " + (x >= 3 ? "many" : "few")
end

squares = numbers.map {|x| x * x}
print squares, "\n"


# Whenever a block is appended to a method call, Ruby automatically converts
# it to a Proc object but one without an explicit name. The method, however,
# has a way to access this Proc, by means of the yield statement.
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

do_twice lambda {puts "Hola"}


# Code blocks by themselves are fun, and they can take params.
def parameters
	puts 'Here, have two random numbers.'
	yield rand(10), rand(50) if block_given?
	puts 'Now say thank you!'
end
parameters do |x,y| puts "#{x}, #{y}" end


# Example usage from vagrant.
def config_vm_define (vm_name)
  print "Configure vm ", vm_name, "\n"
  yield "Provide a host object to configure."
end

config_vm_define "Host1" do |host|
  puts host
end
