# Procs are defined as follows: Proc objects are blocks of code that have
# been bound to a set of local variables. Once bound, the code may be called
# in different contexts and still access those variables.

def gen_times(factor)
  return Proc.new {|n| n*factor }
end

times3 = gen_times(3)           # 'factor' is replaced with 3
times5 = gen_times(5)

puts times3.call(12)                 #=> 36
puts times5.call(5)                  #=> 25
puts times3.call(times5.call(4))     #=> 60


# Procs in Ruby are first-class objects, since they can be created during
# runtime, stored in data structures, passed as arguments to other functions
# and returned as the value of other functions.
def foo(a, b)
  a.call(b)
end

# 'putser' accepts one parameter and print it. Equivalent:
#   putser = lambda {|x| puts x}
putser = Proc.new {|x| puts x}
foo(putser, 34)
