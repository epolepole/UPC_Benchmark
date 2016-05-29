#!/bin/bash

cd build
#rm -fr *
cmake .. -DTEST_TO_RUN=mult_matrices -DTHREADS=8
#cmake .. -DTEST_TO_RUN=mult_matrices
make