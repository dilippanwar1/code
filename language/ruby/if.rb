# Experiment with ruby if condition.


democrats = ["Carter", "Clinton"]
republicans = ["Ford", "Reagan", "Bush1", "Bush2"]
party = ARGV[0]

if party == nil
	print "Argument must be \"democrats\" or \"republicans\"\n"
elsif party == "democrats"
	democrats.each { |i| print i, " "}
	print "\n"
elsif party == "republicans"
	republicans.each { |i| print i, " "}
	print "\n"
else
	print "All presidents since 1976 were either Democrats or Republicans\n"
end


# The if keyword can follow the action instead of preceding it:
if party != nil
	democrats.each { |i| print i, " "} if party == "democrats"
	republicans.each { |i| print i, " "} if party == "republicans"
	if (party != "democrats" && party != "republicans")
	  print "All presidents since 1976 were either Democrats or Republicans"
  end
  print "\n"
end
