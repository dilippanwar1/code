#!/bin/bash
#
# Shell parameter expansion
# http://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html

#
# ${parameter:-word}
# If parameter is unset or null, the expansion of word is substituted. Otherwise,
# the value of parameter is substituted.
#
word=${1:-"first param is unset or nul"}
echo ${word}

#
# ${parameter-word}
# If parameter is unset, the expansion of word is substituted. Otherwise, the
# value of parameter is substituted.
#
word=${1-"first param not set"}
echo ${word}

#
# ${parameter:=word}
# If parameter is unset or null, the expansion of word is assigned to parameter.
# The value of parameter is then substituted. Positional parameters and special
# parameters may not be assigned to in this way.
#

#
# ${parameter:?word}
# If parameter is null or unset, the expansion of word (or a message to that
# effect if word is not present) is written to the standard error and the shell,
# if it is not interactive, exits. Otherwise, the value of parameter is substituted.
#

#
# ${parameter:+word}
# If parameter is null or unset, nothing is substituted, otherwise the expansion
# of word is substituted.
#
word=${1:+"first param is set and value is $1"}
echo ${word}

#
# Substring expansion, general form:
#  ${parameter:offset}
#  ${parameter:offset:length}
# Start from offset (inclusive), get length characters. If length is empty, then
# expand to the end of string.
#
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
