ss = 4
while ss > 0
	puts ss
	ss -= 1
end

puts "======================"
while ss < 5
	puts ss
	ss += 1
	break if ss > 2
end

puts "======================"
ss = 5
while ss > 0
	puts ss
	ss -= 2
	if ss == 1
		ss += 5
	end
end
