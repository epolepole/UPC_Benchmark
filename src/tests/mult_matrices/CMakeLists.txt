#CMakeLists.txt
file(GLOB test_src "*.h" "*.c")
add_library(${TEST_TO_RUN} STATIC ${test_src})