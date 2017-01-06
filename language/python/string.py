#!/usr/bin/python

# string.lstrip, return a copy of the string with leading characters removed.
print 'pcr12345pcr'.lstrip('pcr')

# string.rstrip, return a copy of the string with trailing characters removed
print 'pcr12345pcr'.rstrip('pcr')

# string.strip, return a copy of the string with leading and trailing
# characters removed
print 'pcr12345pcr'.strip('pcr')

print 'localhost:8000:1020'.rfind(':')
print 'localhost:8000:1020'.find(':')

power_device = '32:CD1-B2-2B-6-1:meter'
colon = power_device.rfind(':')
print power_device[:colon], power_device[colon:]
