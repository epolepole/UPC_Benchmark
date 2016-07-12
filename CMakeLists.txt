#CMakeLists.txt
cmake_minimum_required (VERSION 2.6)

message(STATUS "Starting Project")


set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
message(STATUS  "Lets see what we have here ${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS}")
set(CMAKE_C_COMPILER upcc)

project (Benchmark)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


if(NOT DEFINED THREADS)
	set(THREADS 16)
	message(STATUS "Setting 16 threads")
endif(NOT DEFINED THREADS)

message(STATUS "Compiling for ${THREADS} threads")

set(CMAKE_C_FLAGS_DEBUG "-T ${THREADS} -g")
set(CMAKE_C_FLAGS_RELEASE "-T ${THREADS}")


if(NOT DEFINED TEST_TO_RUN)	
	set(TEST_TO_RUN mult_matrices)
endif(NOT DEFINED TEST_TO_RUN)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -network=mpi")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -network=mpi")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_subdirectory (src)

#enable_testing()
#add_test(NAME check_money COMMAND check_money)
