#CMakeLists.txt
file(GLOB head_files ${CMAKE_CURRENT_SOURCE_DIR} "*.h")
file(GLOB src_files ${CMAKE_CURRENT_SOURCE_DIR} "*.c")
#add_library(${TEST_TO_RUN} STATIC mult_mat.c mult_mat.h T.h)
add_library(${TEST_TO_RUN} STATIC ${src_files} ${head_files})