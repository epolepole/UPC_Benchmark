#include "t1.h"

void init(int argc, const char *argv[]) {
	test_functions[0] = Test1;
	test_functions[1] = Test2;
}

void Test1() {
	//test_text(1);
	//printf("Hello from thread %i/%i\n", MYTHREAD, THREADS);
	upc_barrier;
}

void Test2() {
	//test_text(2);
	upc_forall(int i = 0; i<N; ++i; i%THREADS) {
		//printf("position: %i, value: %f\n",i,my_vector[i]);
		upc_barrier;
	}
}

void test_text(int num) {
	printf("Performing test number %i\n", num);
}