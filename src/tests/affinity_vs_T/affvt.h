#ifndef __BENCH_H_
#define __BENCH_H_

#include <stdio.h>
#include <upc.h>

#ifndef MULTIPLICATION_FACTOR
#define MULTIPLICATION_FACTOR 1
#endif

#define SIZE THREADS*MULTIPLICATION_FACTOR


#ifndef BLOCKING_FACTOR
#define BLOCKING_FACTOR 1
#endif


void adding_names();
void adding_tests();

void dynamic_allocation();  

void local_definition();
void dynamic_definiton();


void multiplication_shared(shared [SIZE] int* A, shared [BLOCKING_FACTOR] int* B, shared [BLOCKING_FACTOR] int* AB);


void multiplication_local(int A[][], int B[][], shared [BLOCKING_FACTOR] int* pAB, int actual_threads);



void free_allocation();




typedef shared int* shared_int_ptr;


static shared [SIZE] int *dA;  // POINTER FOR DYNAMIC ALLOCATION
static shared [BLOCKING_FACTOR] int *dB;  // POINTER FOR DYNAMIC ALLOCATION
static shared [BLOCKING_FACTOR] int *dAB; // POINTER FOR DYNAMIC ALLOCATION

int lA[SIZE][SIZE];
int lB[SIZE][SIZE];


int n_blocks;
int actual_threads;


#endif // __BENCH_H_
