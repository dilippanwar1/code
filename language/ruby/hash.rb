# Experiment with ruby hash.


# Initialize hash with three elements via hash literal.
litt = {"lname" => "Litt", "fname" => "Steve", "ssno" => "123456789"}
print "Lastname              : ", litt["lname"], "\n"
print "Firstname             : ", litt["lname"], "\n"
print "Social Security Number: ", litt["ssno"],  "\n"
print "\n"


# Hash can also be created using new.
names = Hash.new
names[1] = "Jane"
names[2] = "Thomas"
names.store(3, "Rebecca")
puts names                 # => {1=>"Jane", 2=>"Thomas", 3=>"Rebecca"}


# Ruby symbols (e.g. :de) are commonly used as hash key.
domains = {
  :de => "Germany", :sk => "Slovakia",
  :no => "Norway", :us => "United States"
}


# Add a new key and update an existing key.
litt["gender"] = "male"
litt["ssno"] = "987654321"

print "Corrected Social Security Number: ", litt["ssno"], "\n"
print "Gender                          : ", litt["gender"], "\n"
print "\n"
print "Hash length is ", litt.length, "\n"
print "Hash class  is ", litt.class, "\n"
print "\n"


# Hash value can be other types of classes.
people = {
	"torvalds" => {
    "lname" => "Torvalds", "fname" => "Linus", "job" => "maintainer"
  },
	"matsumoto" => {
    "lname" => "Matsumoto", "fname" => "Yukihiro", "job" => "Ruby originator"
  },
	"litt" => {
    "lname" => "Litt", "fname" => "Steve", "job" => "troubleshooter"
  },                            # This final comma is optional.
}


# Some methods on hash.
puts people.keys.inspect
puts people.values.inspect
puts people.empty?              # => false
people2 = people.dup            # Make a duplicate of 'people'.
puts people2.eql? people        # => true
people2.clear
puts people2.empty?             # => true
print "\n"
puts domains.has_key? :de       # => true
puts domains.include? :no       # => true
puts domains.key? :me           # => false
puts domains.member? :sk        # => true


# Loop through hash.
keys = people.keys
for key in 0...keys.length
	print "key  : ", keys[key], "\n"
	print "lname: ", people[keys[key]]["lname"], "\n"
	print "fname: ", people[keys[key]]["fname"], "\n"
	print "job  : ", people[keys[key]]["job"], "\n"
	print "\n"
end
