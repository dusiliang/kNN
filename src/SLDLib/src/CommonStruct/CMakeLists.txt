set (LIBRARY_OUTPUT_PATH ${SLD_LIB_SOURCE_DIR}/lib)
set (SRC_LIST SLDString.cpp)

set (CMAKE_C_COMPILER g++)

include_directories (${SLD_LIB_SOURCE_DIR}/include)

add_library (SLDString ${SRC_LIST})