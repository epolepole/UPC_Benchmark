#!/bin/bash

cd build/bin
upcrun -shared-heap 2GB -q Benchmark 100 >> ../../output/results.txt
#upcrun -freeze=0 Benchmark 100