#!/bin/bash
#
# A here script (also sometimes called a here document) is an additional form of
# I/O redirection. It provides a way to include content that will be given to the
# standard input of a command. In the case of the script below, the standard input
# of the cat command was given a stream of text from our script.
# A here script is constructed like this:
#  command << token
#   content to be used as command's standard input
#  token
# Where 'token' can be any string of characters.
# Here doc with pipe:
#  cat << EOF | cmd
#    text
#  EOF

cat <<EOF
<html>
<head>
    <title>
    The title of your page
    </title>
</head>

<body>
    Your page content goes here.
</body>
</html>
EOF

cat <<EOF | xargs echo
---
  Your page content goes here.
---
EOF
