cmake_minimum_required(VERSION 2.8.9)
project (TestLibrary)

# For shared library:
set(PROJECT_LINK_LIBS libtestStudent.so)
link_directories(~/code/tool/cmake/shared-lib/build)

# For static library (example not added yet):
#
# set(PROJECT_LINK_LIBS libtestStudent.a)
# link_directories(~/code/tool/cmake/static-lib/build)

include_directories(~/code/tool/cmake/shared-lib/include)

add_executable(libtest libtest.cpp)
target_link_libraries(libtest ${PROJECT_LINK_LIBS})
