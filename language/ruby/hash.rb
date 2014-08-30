# Initialize hash with three elements.
litt = {"lname"=>"Litt", "fname"=>"Steve", "ssno"=>"123456789"}
print "Lastname              : ", litt["lname"], "\n"
print "Firstname             : ", litt["lname"], "\n"
print "Social Security Number: ", litt["ssno"],  "\n"
print "\n"

# Add a new key and update an existing key.
litt["gender"] = "male"
litt["ssno"] = "987654321"

print "Corrected Social Security Number: ", litt["ssno"], "\n"
print "Gender                          : ", litt["gender"], "\n"
print "\n"
print "Hash length is ", litt.length, "\n"
print "Hash class  is ", litt.class, "\n"


# Hash value can be other types of classes.
people = {
	"torvalds"=>{"lname"=>"Torvalds", "fname"=>"Linus", "job"=>"maintainer"},
	"matsumoto"=>{"lname"=>"Matsumoto", "fname"=>"Yukihiro", "job"=>"Ruby originator"},
	"litt"=>{"lname"=>"Litt", "fname"=>"Steve", "job"=>"troubleshooter"}
}

keys = people.keys

for key in 0...keys.length
	print "key  : ", keys[key], "\n"
	print "lname: ", people[keys[key]]["lname"], "\n"
	print "fname: ", people[keys[key]]["fname"], "\n"
	print "job  : ", people[keys[key]]["job"], "\n"
	print "\n\n"
end
