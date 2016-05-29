#ifndef __BENCH_H_
#define __BENCH_H_

#include <stdio.h>
#include <upc.h>


typedef shared int* shared_int_ptr;
typedef shared int* shared shared_int_shared_ptr;

shared int A[THREADS][THREADS], B[THREADS][THREADS], AB[THREADS][THREADS];
shared_int_ptr row_ptr[THREADS];
shared_int_ptr pAB;


#endif // __BENCH_H_