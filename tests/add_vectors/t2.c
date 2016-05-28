#include "t2.h"

void init(int argc, const char *argv[]) {
	test_functions[0] = Test1;
	test_functions[1] = Test2;
	if (MYTHREAD==0) 
		srand(0);
 	
 	upc_barrier;

	upc_forall (int i=0; i < N; ++i; i%THREADS){
		vec_1[i] = rand();
		vec_2[i] = rand();
	}
}

void Test1() {
	upc_forall(int i=0; i< N; ++i; i%THREADS) {
		vec_3[i] = vec_1[i] + vec_2[i];
	}
}

void Test2() {
	
}