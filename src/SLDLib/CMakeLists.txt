cmake_minimum_required (VERSION 2.6)
project (SLD_LIB)

set (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g")
set (CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall -O2")

add_subdirectory (src)