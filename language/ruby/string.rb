# Experiment with ruby string.


# Combining strings with non-strings using the plus sign + can be hard to
# read, and prone to error:
puts "The result of 7 + 7 is " + (7 + 7).to_s


# It's very easy to forget to miss a plus sign or closing quote when combining
# strings. Luckily, Ruby has a special notation that allows us to evaluate
# Ruby code and output the result into a String - within that String:
puts "The result of 7 + 7 is #{7+7}"
puts "#{10 * 10} is greater than #{9 * 11}"


# Noth that things between #{} should be valid Ruby code.
puts "No interpolation here.upcase"
# => No interpolation here.upcase

puts "This is interpolation #{"here".upcase}"
# => This is interpolation HERE

puts "This is not useful interpolation #{"here.upcase"}"
# => This is not useful interpolation here.upcase

# The following puts is not valid, because 'here' will be interpreted as a
# variable or a method.
# puts "This is an error #{here.upcase}"

master = "master-10.0.0.1"
puts "Kubernetes-#{master}"
# => Kubernetes-master-10.0.0.1
