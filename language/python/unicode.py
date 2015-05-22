# -*- coding: utf-8 -*-
# The above line is mandatory when working with non-ascii characters. It
# tells Python how to encode non-ascii characters.
#
# Also, because this file contains non-asicii character, the file is encoded
# using utf-8 by default. While other files usually are encoded using ascii.
#
# Unicode in Python (Python 2)
# http://farmdev.com/talks/unicode/
# http://betterexplained.com/articles/unicode/
# http://www.joelonsoftware.com/articles/Unicode.html

import codecs

# -----------------------------
# Define a base string (not a unicode string). Because we've specified the
# default coding schema in the first line as UTF-8, this will be a string
# of bytes encoded with UTF-8.  This is equivalent of:
# >> ivan = u'ivanć'
# >> ivan_utf8 = ivan.encode('utf-8')
ivan_utf8 = 'ivanć'

# The byte representation, note here ć takes up two bytes:
#          i      v       a       n       ć
# hex      \x69  \x76    \x61    \x6e   \xc4\x87
# decimal  105    118     97      110
#
# Also note that different coding schema gives different results:
# letter   UTF-8      UTF-16    Shift-JIS
# ć       \xc4\x87   \x07\x01    \x85\xc9
print ivan_utf8                 # ivanć
print repr(ivan_utf8)           # 'ivan\xc4\x87'
print type(ivan_utf8)           # <type 'str'>
print len(ivan_utf8)            # 6

# Now we write the string to file. The newly created file will be utf-8
# encoded. (Check with $file -bi /tmp/file_utf8.dat). When open in text
# mode, it will display 'ivanć'; when open in hex mode, it will display
# 6976 616e c487. The file is 6 bytes in length.
with open('/tmp/file_utf8.dat', 'w') as f:
  f.write(ivan_utf8)


# -----------------------------
# ''.encode() converts <type 'unicode'> to <type 'str'>
# ''.decode() converts <type 'str'> to <type 'unicode'>
# The following code won't work since default coding schema in Python 2 is
# ascii, so we can't decode utf-8 encoded string. Same applies for other
# coding schema.
if False:
  ivan_unicode = ivan_utf8.decode() # Error
  ivan_unicode = ivan_utf8.decode('utf-7') # Error
# We can of course decode the string with utf-8. Upon successful decode, we
# get u'ivan\u0107'. This is a way to represent text without bytes.
ivan_unicode = ivan_utf8.decode('utf-8')
print ivan_unicode                  # ivanć
print repr(ivan_unicode)            # u'ivan\u0107'
print type(ivan_unicode)            # <type 'unicode'>
print len(ivan_unicode)             # 5

# We can't write ivan_unicode to file directly using open()->write(), because
# there is no way for write() to know how to encode the unicode. i.e. Alawys
# specify encoding when saving a unicode to disk.
if False:
  with open('/tmp/file_uni.dat', 'w') as f:
    f.write(ivan_unicode)       # Error
# Even though the unicode is created with utf-8 encoding. We have to do
#   >> f.write(ivan_unicode_again.encode('utf-8'))
if False:
  ivan_unicode_again = unicode('ivanć', 'utf-8')
  with open('/tmp/file_uni.dat', 'w') as f:
    f.write(ivan_unicode_again) # Error

# A shortcut is to use codecs library.
with codecs.open('/tmp/file_uni.dat', 'w', encoding='utf-8') as f:
  f.write(ivan_unicode)


# -----------------------------
# As above, different encoding of unicode yields different byte string.
ab = unicode('AB')              # Same as u'AB'
print repr(ab.encode('utf-8'))  # AB
print repr(ab.encode('utf-16')) # \xff\xfeA\x00B\x00

# Since default coding schema in Python 2 is ascii, we can't create the following
# variable: coding schema is required. In Python 3, utf-8 is the default.
if False:
  abc = unicode('ABć')

# Error: decoding Unicode is not supported
if False:
  abab = unicode(u'AB', 'utf-8')

# In Python source code, Unicode literals are written as strings prefixed
# with the ‘u’ or ‘U’ character. Specific code print can use '\u', which
# expects 4 hex digits; '\U' expects 8 hex digits; '\x' expects 2 hex digits.
s = u"a\xac\u1234\u20ac\U00008000"
for c in s: print ord(c),
print
