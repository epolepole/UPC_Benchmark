#ifndef __BENCH_H_
#define __BENCH_H_

#include <stdio.h>
#include <upc.h>


#define MULTIPLICATION_FACTOR 3
#define SIZE THREADS*MULTIPLICATION_FACTOR

typedef shared int* shared_int_ptr;


int A_local[SIZE][SIZE], B_local[SIZE][SIZE], AB_local[SIZE][SIZE];


shared int A[SIZE][SIZE], B[SIZE][SIZE], AB[SIZE][SIZE];


shared_int_ptr row_ptr[MULTIPLICATION_FACTOR*SIZE];
shared_int_ptr pB;
shared_int_ptr pAB;
int *col_ptr;


#endif // __BENCH_H_