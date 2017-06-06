cmake_minimum_required(VERSION 2.8.9)
project(directory_test)

# The include_directories() function is used to bring the header files into
# the build environment.
include_directories(include)

# The set(SOURCES … ) function can be used to set a variable (SOURCES) that
# contains the name values of all of the source files (.cpp) in the project.
# However, because each source file must be added manually the next line is
# used in its place, and this line is commented out.
#
# set(SOURCES src/mainapp.cpp src/student.cpp)

# The file() command is used to add the source files to the project. GLOB
# (or GLOB_RECURSE) is used to create a list of all of the files that meet
# the globbing expression (i.e., “src/*.cpp“) and add them to a variable SOURCES.
file(GLOB SOURCES "src/*.cpp")

# The add_executable() function uses the SOURCES variable, rather than an
# explicit reference to each source file, in order to build the testStudent
# executable program.
add_executable(testStudent ${SOURCES})


# For this example, I wish to place all of the build files in the build directory,
# which is achieved very simply by calling the cmake program from within the
# build directory.
#  $ cd build
#  $ cmake ..
#
# The build directory then contains the Makefile for the project, which correctly
# refers to the files in the src and include directories.
#  $ make
#  $ ./testStudent
