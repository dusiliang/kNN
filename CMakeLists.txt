cmake_minimum_required (VERSION 2.6)
project (IMAGE_RECOGNIZOR)

set (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
set (CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")

add_subdirectory (src)
