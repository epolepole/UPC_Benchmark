#ifndef __T_H_
#define __T_H_

#include <stdio.h>
#include <upc.h>

#define N_Tests 5

void init(int argc, const char *argv[]);
void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void end_test();

typedef void(*function_ptr)();

function_ptr test_functions[N_Tests];
const char * test_names[N_Tests];

#endif // __T_H_