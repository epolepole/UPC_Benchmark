#include <upc_relaxed.h>
#include <stdio.h>

#define N 100*THREADS
#define N_Tests 2

static void test_text(int num);

void init(int argc, const char *argv[]);

void Test1();
void Test2();

void(* test_functions[N_Tests]) ();

const char * test_names = {"Test1", "Test2", "Test3"};

shared double my_vector [N];
