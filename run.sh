#!/bin/bash

cd build/bin
if [ $1 == "R" ] ; then
	upcrun Benchmark $2 
else
	upcrun -q -backtrace -freeze=0 Benchmark $2
fi
cd ../../