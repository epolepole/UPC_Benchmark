#ifndef _MEMORY_H_
#define _MEMORY_H_
#include <stdio.h>
#include <upc.h>

// IF BLOCKING FACTOR ==1, AFFINITY IS USED.
// ELSE, ALL THE THREADS ARE USED (so to say)
#ifndef BLOCKING_FACTOR
#define BLOCKING_FACTOR 1
#endif

void initialization (shared [BLOCKING_FACTOR] int* *A, shared [BLOCKING_FACTOR] int* *B, shared [BLOCKING_FACTOR] int* *AB, int n_blocks, int SIZE);
void multiplication(shared [BLOCKING_FACTOR] int* A, shared [BLOCKING_FACTOR] int* B, shared [BLOCKING_FACTOR] int* AB, int SIZE);
void print(shared [BLOCKING_FACTOR] int* A, shared [BLOCKING_FACTOR] int* B, shared [BLOCKING_FACTOR] int* AB, int SIZE);


const char * test_names = {"Test1", "Test2", "Test3"};

#endif