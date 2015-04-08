# Experiment with ruby symbol.

# A Ruby symbol is a thing that has both a number (integer) representation
# and a string representation. It's not string.

# Most symbols looks like a colon followed by a non-quoted string.
:myname

# Another way to make a symbol is with a colon followed by a quoted string.
:"Steve was here and now is gone"

# One can also output symbol.
puts :love                      # implicitly call 'to_s'
puts :love.to_s
puts :love.object_id
puts :love.class                # => Symbol
puts :'I love Ruby.'


# Symbols are immutable. Their value remains constant during the entirety of
# the program. They never appear on the left side of an assignment.
# Error: :myname = "steve"

# Also, multiple uses of the same symbol have the same object ID and are the
# same object.
puts :myvalue.object_id         # 839708
puts :myvalue.object_id         # 839708
puts "myvalue".object_id        # 69875333216940
puts "myvalue".object_id        # 69875333216880
