a = [ "a", "b", "c", "d" ]

# 'collect' Invokes the given block once for each element of self.
# Creates a new array containing the values returned by the block.
print a.collect { |x| x + "!" }
print "\n"
print a, "\n"


words = ["alpha", "beta", "gamma"]
puts words.collect {
	|word|
	word.capitalize
}
puts "======================"
upperWords = words.collect do
	|word|
	word.capitalize
end
puts upperWords
