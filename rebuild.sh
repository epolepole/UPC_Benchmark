#!/bin/bash

mkdir build
cd build
#rm -fr *
cmake .. -DTEST_TO_RUN=mult_matrices -DTHREADS=8 -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_BUILD_TYPE=Release
#cmake .. -DTEST_TO_RUN=pointers -DTHREADS=8
#cmake .. -DTEST_TO_RUN=mult_matrices
make verbose=1
