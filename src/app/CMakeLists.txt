set (EXECUTABLE_OUTPUT_PATH ${IMAGE_RECOGNIZOR_SOURCE_DIR}/bin)
set (SRC_LIST main.cpp DataProcessor.cpp PictureInfo.cpp LabeledDataProcessor.cpp)

include_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/src/knn)
include_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/src/SLDLib/include)

link_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/lib)
link_directories (${IMAGE_RECOGNIZOR_SOURCE_DIR}/src/SLDLib/lib)

add_executable (image_recognizor ${SRC_LIST})
target_link_libraries (image_recognizor SLDString knn SLDConfig)