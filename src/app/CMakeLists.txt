set (EXECUTABLE_OUTPUT_PATH ${IMAGE_RECOGNIZOR_SOURCE_DIR}/bin)
set (SRC_LIST main.cpp DataProcessor.cpp PictureInfo.cpp)

include_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/src/mylib)
include_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/src/knn)

link_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/lib)

add_executable (image_recognizor ${SRC_LIST})
target_link_libraries (image_recognizor mylib knn)