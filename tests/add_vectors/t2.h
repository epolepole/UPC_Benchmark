#include <upc_relaxed.h>
#include <stdio.h>

#define N 10000*THREADS
#define N_Tests 2

void init();

void Test1();
void Test2();

void(* test_functions[N_Tests]) ();

static shared double vec_1 [N];
static shared double vec_2 [N];
static shared double vec_3 [N]; 


