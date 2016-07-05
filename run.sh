#!/bin/bash

cd build/bin
#upcrun -q Benchmark 1000 >> ../../output/results.txt
upcrun -q Benchmark 1000 
#upcrun -freeze=0 Benchmark 100
