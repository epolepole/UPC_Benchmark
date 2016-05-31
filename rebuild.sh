#!/bin/bash

cd build
#rm -fr *
cmake .. -DTEST_TO_RUN=mult_matrices -DTHREADS=8 -DCMAKE_VERBOSE_MAKEFILE=OFF
#cmake .. -DTEST_TO_RUN=pointers -DTHREADS=8
#cmake .. -DTEST_TO_RUN=mult_matrices
make verbose=1