# The elipses (...) indicate the range through which to loop.
# The for is terminated by an end. You don't need braces for a loop.

for i in 1...10                 # (...) exclusive of 10
  print i, " Hello\n";
end

for i in 1..3                   # (..) inclusive of 3
  print i, " Hello Again\n";
end

# Loop an array.
presidents = ["Ford", "Carter", "Reagan", "Bush1", "Clinton", "Bush2"]
for i in 0...presidents.length
	print i, ": ", presidents[i], "\n";
end

# Loop an array backward.
presidents = ["Ford", "Carter", "Reagan", "Bush1", "Clinton", "Bush2"]
for i in 0...presidents.length
	print i, ": ", presidents[-i-1], "\n";
end
