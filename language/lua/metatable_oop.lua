#!/usr/bin/env lua

BaseClass = {}

function BaseClass:new(o)
  local o = o or {}
	setmetatable(o, self)
  self.__index = self
  return o
end

function BaseClass:hello(name)
  print("hello " .. name)
end


ChildClass = BaseClass:new()

function ChildClass:hello2(name)
  print("hello again ".. name)
end


ChildClass:hello('deyuan')
ChildClass:hello2('deyuan')
