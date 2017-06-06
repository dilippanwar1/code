# The first line sets the minimum version of CMake for this project.
cmake_minimum_required(VERSION 2.8.9)

# The second line is the project() command that sets the project name.
project (hello)

# The third line is the add_executable() command, which requests that
# an executable is to be built using the helloworld.cpp source file.
add_executable(hello helloworld.cpp)
