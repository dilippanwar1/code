#!/bin/bash
# Several Shell Examples

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
