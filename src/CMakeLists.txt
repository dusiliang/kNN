set (SRC_LIST main.cpp DataProcessor.cpp PictureInfo.cpp mylib.cpp knn.cpp)
set (LIBRARY_OUTPUT_PATH ${kNN_SOURCE_DIR}/lib)

add_executable (kNN ${SRC_LIST})
