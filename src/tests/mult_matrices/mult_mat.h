#ifndef __BENCH_H_
#define __BENCH_H_

#include <stdio.h>
#include <upc.h>

#ifndef MULTIPLICATION_FACTOR
#define MULTIPLICATION_FACTOR 2
#endif

#define SIZE THREADS*MULTIPLICATION_FACTOR


#ifndef BLOCKING_FACTOR
#define BLOCKING_FACTOR 1
#endif


void adding_names();
void adding_tests();
void dynamic_allocation();  
void shared_definition();
void local_definition();
void dynamic_definiton();
void free_allocation();




typedef shared int* shared_int_ptr;


int A_local[SIZE][SIZE], B_local[SIZE][SIZE], AB_local[SIZE][SIZE];


static shared [BLOCKING_FACTOR] int *dA;  // POINTER FOR DYNAMIC ALLOCATION
static shared [BLOCKING_FACTOR] int *dB;  // POINTER FOR DYNAMIC ALLOCATION
static shared [BLOCKING_FACTOR] int *dAB; // POINTER FOR DYNAMIC ALLOCATION
int n_blocks;
int dSIZE;

shared int A[SIZE][SIZE], B[SIZE][SIZE], AB[SIZE][SIZE];


shared_int_ptr row_ptr[MULTIPLICATION_FACTOR*SIZE];
shared_int_ptr pB;
shared_int_ptr pAB;
int *col_ptr;


#endif // __BENCH_H_