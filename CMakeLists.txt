#CMakeLists.txt

set(CMAKE_C_COMPILER upcc)

cmake_minimum_required (VERSION 2.6)
project (Benchmark)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


if(NOT DEFINED THREADS)
	set(THREADS 8)
	message(STATUS "Setting 8 threads")
endif(NOT DEFINED THREADS)

message(STATUS "Compiling for ${THREADS} threads")

set(CMAKE_C_FLAGS_DEBUG "-T ${THREADS} -g")
set(CMAKE_C_FLAGS_RELEASE "-T ${THREADS}")


if(NOT DEFINED TEST_TO_RUN)	
	set(TEST_TO_RUN mult_matrices)
endif(NOT DEFINED TEST_TO_RUN)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_subdirectory (src)

#enable_testing()
#add_test(NAME check_money COMMAND check_money)