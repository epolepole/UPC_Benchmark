#CMakeLists.txt
include_directories(${CMAKE_SOURCE_DIR}/src/tests/${TEST_TO_RUN})
#add_executable(Benchmark ${TEST_TO_RUN})
add_executable(Benchmark main.c)
target_link_libraries(Benchmark ${TEST_TO_RUN})