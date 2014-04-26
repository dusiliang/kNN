set (LIBRARY_OUTPUT_PATH ${IMAGE_RECOGNIZOR_SOURCE_DIR}/lib)
set (SRC_LIST knn.cpp LabeledKnn.cpp TrainData.h)

set (CMAKE_C_COMPILER c++)

include_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/src/mylib)

add_library(knn ${SRC_LIST})