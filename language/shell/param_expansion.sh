#!/bin/bash
#
# Shell parameter expansion
# http://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html

# Substring expansion, general form:
#  ${parameter:offset}
#  ${parameter:offset:length}
# Start from offset (inclusive), get length characters. If length is empty, then
# expand to the end of string.
hash="93279e3308bdbbeed946fc965017f67a"
echo ${hash:0:5}                # Output: 93279
echo ${hash:3:4}                # Output: 79e3
echo ${hash:10}                 # Output: bdbbeed946fc965017f67a

# Remove string out of string.
fullpath="/media/somepath/dir/helloworld/src"
rootpath="/media/somepath/dir"
echo ${fullpath#${rootpath}}

# Same as above string operation, but here we remove pattern *@. *@ is expanded
# as a glob, and string that matches *@ will be deleted from original string. Note
# here we can't use ip_addr=${ssh_info#"*@"} - the quote will make *@ a string and
# bash will not expand it.
ssh_info="vagrant:vagrant@192.168.205.10"
ip_addr=${ssh_info#*@}
echo ${ip_addr}
