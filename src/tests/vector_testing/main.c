#include <upc_relaxed.h>

#include <stdio.h>
#define N 100*THREADS

void test_text(int num);
void Test1();
void Test2();


shared double my_vector [N];

int main() {
	Test1();
	Test2();
	return 0;
}

void Test1() {
	test_text(1);
	printf("Hello from thread %i/%i\n", MYTHREAD, THREADS);
	upc_barrier;
}

void Test2() {
	test_text(2);
	upc_forall(int i = 0; i<N; ++i; i%THREADS) {
		printf("position: %i, value: %f\n",i,my_vector[i]);
		upc_barrier;
	}
}

void test_text(int num) {
	printf("Performing test number %i\n", num);
}