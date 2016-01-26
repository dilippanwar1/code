#!/bin/bash
#
# Shell misc examples

# The characters "$( )" tell the shell, "substitute the results of the enclosed
# command". The older backtick form also works, but try to avoid it.
echo $(date +"%x %r %Z")
echo `date +"%x %r %Z"`


# 'cat /dev/urandom' returns unlimited random characters (non-blocking);
#   /dev/random is blocking.
# 'base64' is the commandline util to do base64 conversion, e.g.
#   echo "deyuan" | base64 => ZGV5dWFuCg==
# 'tr' - translate or delete characters, here '-d' means delete charaters, e.g.
#   echo "abcd=cdef=+vfe" | tr -d "=f" => abcdcde+ve
# 'dd' - convert and copy a file. 'dd bs=32 count=1' means copy 32x1 bytes.
#   The default output is stdout, and input is stdin; can be overriden by
#   -if and -of.
# The following sequence of commands will create a random string of 32 Bytes.
TOKEN=$(cat /dev/urandom | base64 | tr -d "=+/" | dd bs=32 count=1 2> /dev/null)
echo ${TOKEN}


# 'umask' return, or set, the value of the system's file mode creation mask.
# The following command will create a /tmp/token_file with the token string;
# it has mode user=read/write, group=<none>, other=<none>
(umask u=rw,go= ; echo "${TOKEN}" > /tmp/token_file)


# Use 'sed' to get volume id from the volume path. Here, s|.*/\(.*\)/_data$|\1|
# matches the volume id. \(.*\) is a grouping and \1 returns this grouping.
# Seed 's' command in 'info sed' man page.
echo "/var/lib/docker/volumes/323c67398780781e23099a97391d4e5c84099ef6cedef910069db107c4a88d6e/_data" | \
  sed 's|.*/\(.*\)/_data$|\1|;s|.*/\([0-9a-f]\{64\}\)$|\1|'

# Equivalent to `docker ps -a -q --no-trunc`. NR is a built in variable in awk
# meaning number of records (lines) scanned so far. Another commonly used one
# is NF - number of fileds in current record.
docker ps -a --no-trunc | awk '{ if (NR != 1) print $1 }'
