#include <stdio.h>
#include <upc.h>

int size;

int main(int argc, const char *argv[]) {
	if (argc==2) {
		size = atoi(argv[1]);
	}
	else size = 8;

	THREADS = size;
	prinf("%i from %i", MYTHREAD, THREADS);
	return 0;
	
}