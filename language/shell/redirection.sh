#!/bin/bash

# Redirect stdout to file "File".
echo "Redirect from stdout" > File

# Samething, redirect stdout to file "File".
echo "Redirect from stdout" 1> File

# Redirect and append stdout to file "File".
echo "Redirect and append from stdout" 1>> File

# Redirct stderr to file "File".
make 2> File

# Redirect both stdout and stderr to file "File".
echo "Redirect both stdout and stderr" &> File

# Multiple lines
(
  echo "#! /bin/bash"
  echo "echo ComeOn"
) > File

# Combine stdout and stderr to stdout
# Here is one way to remember this construct (altough it is not entirely
# accurate): at first, 2>1 may look like a good way to redirect stderr to
# stdout. However, it will actually be interpreted as "redirect stderr to
# a file named 1". & indicates that what follows is a file descriptor and
# not a filename. So the construct becomes: 2>&1.
make 2>&1
