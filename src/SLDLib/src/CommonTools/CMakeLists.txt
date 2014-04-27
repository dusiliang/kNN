set (LIBRARY_OUTPUT_PATH ${SLD_LIB_SOURCE_DIR}/lib)
set (SRC_LIST SLDConfig.cpp)

set (CMAKE_C_COMPLIER g++)

include_directories (${SLD_LIB_SOURCE_DIR}/include)

add_library(SLDConfig ${SRC_LIST})