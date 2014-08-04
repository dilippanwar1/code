#!/usr/bin/env lua

do
  a = 6
  print(a)
end

print(a)

for i = 1,3 do
  print(i)
end

-- nil
print(i)


function foo()
  local a = 10
end

function bar()
  local a = 11
end

foo()
bar()
foo()
print(a)
