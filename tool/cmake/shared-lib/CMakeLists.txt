cmake_minimum_required(VERSION 2.8.9)
project(directory_test)

# The set(CMAKE_BUILD_TYPE Release) function is used to set the build type
# to be a release build.
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

# instead of the add_executable() function that is used in previous examples,
# this example uses the add_library() function. The library is built as a
# shared library using the SHARED flag (other options are: STATIC or MODULE),
# and the testStudent name is used as the name of the shared library.
add_library(testStudent SHARED ${SOURCES})

# The last line uses the install() function to define an installation location
# for the library (in this case it is /usr/lib). Deployment is invoked using
# a call to 'sudo make install' in this case.
install(TARGETS testStudent DESTINATION /usr/lib)
