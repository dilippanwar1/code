# Experiment with ruby proc.  Read block.rb first.


# Procs are short for Procedures, and are defined as follows:
# Proc objects are blocks of code that have been bound to a set of local
# variables. Once bound, the code may be called in different contexts and
# still access those variables.


# To begin with, following is the most common used block.
array = [1, 2, 3, 4]
array.collect! do |n|
  n ** 2
end
puts array.inspect


# To mimic the behavior, we can define our own class.
class Array
  def iterate!
    self.each_with_index do |n, i|
      self[i] = yield(n)
    end
  end
end
# Same as built-in collect! method.
array = [1, 2, 3, 4]
array.iterate! do |n|
  n ** 2
end
puts array.inspect


# Note how we call block code using yield. Using yield is one way to use your
# block of code, however there is another: by calling it as a Proc. There are
# two difference:
# 1. First, we are passing an ampersand argument called &code. This argument
#    is, conveniently enough, our block.
# 2. The second is in the middle of our iterate! method definition, where
#    instead of using yield, we send call to our block of code.
class Array
  def iterate!(&code)
    self.each_with_index do |n, i|
      self[i] = code.call(n)
    end
  end
end

array = [1, 2, 3, 4]
array.iterate! do |n|
  n ** 2
end
puts array.inspect


# Actually, a block is just a Proc. Note as with the above example, we can
# explicitly state that we expect this method to possibly take a block, this
# is what & is for.
def what_am_i(&block)
  block.class
end

puts what_am_i {}               # => Proc


# Blocks are very handy and syntactically simple, however we may want to have
# many different blocks at our disposal and use them multiple times.
# Example1: Use the same proc multiple times.
class Array
  def iterate!(code)
    self.each_with_index do |n, i|
      self[i] = code.call(n)
    end
  end
end

array_1 = [1, 2, 3, 4]
array_2 = [2, 3, 4, 5]
square = Proc.new do |n|
  n ** 2
end
array_1.iterate!(square)
array_2.iterate!(square)
puts array_1.inspect
puts array_2.inspect

# Example2: One or more callbacks
def callbacks(procs)
  procs[:starting].call
  puts "Still going"
  procs[:finishing].call
end
# => Starting
# => Still going
# => Finishing
callbacks(:starting => Proc.new { puts "Starting" },
          :finishing => Proc.new { puts "Finishing" })


# Procs in Ruby are first-class objects, since they can be created during
# runtime, stored in data structures, passed as arguments to other functions
# and returned as the value of other functions.
def foo(a, b)
  a.call(b)
end
# 'putser' accepts one parameter and print it. Equivalent:
#    putser = lambda {|x| puts x}
putser = Proc.new {|x| puts x}
foo(putser, 34)


# gen_times returns a Proc, which we then invoke via call().
def gen_times(factor)
  return Proc.new {|n| n*factor }
end

times3 = gen_times(3)           # 'factor' is replaced with 3
times5 = gen_times(5)
puts times3.class                # => Proc
puts times3.call(12)             # => 36
puts times5.call(5)              # => 25
puts times3.call(times5.call(4)) # => 60
