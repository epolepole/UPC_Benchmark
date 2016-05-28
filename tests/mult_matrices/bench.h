#ifndef __BENCH_H_
#define __BENCH_H_

#include <stdio.h>
#include <upc.h>

#define N_Tests 3


typedef shared int* shared_int_ptr;
typedef shared int* shared shared_int_shared_ptr;

shared int A[THREADS][THREADS], B[THREADS][THREADS], AB[THREADS][THREADS];
shared_int_ptr row_ptr[THREADS];
shared_int_ptr *pAB;


void init(int argc, const char *argv[]);
void Test1();
void Test2();
void Test3();

typedef void(*function_ptr)();

function_ptr test_functions[N_Tests];
const char * test_names[N_Tests];

#endif // __BENCH_H_