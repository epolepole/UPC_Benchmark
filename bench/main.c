#include "t1.h"
#include <time.h>
#include <float.h>

//http://stackoverflow.com/questions/5248915/execution-time-of-c-program
clock_t begin, end;
double time_spent;

double time_min = DBL_MAX;
double time_max = 0;
double time_av = 0;
double time_sum = 0;

int n_iter = 1;

void checkTimes(double time_spent);




int main(int argc, const char * argv[]) {
	
	if (argc == 2)
		n_iter = atoi(argv[1]);
	init();
	for (int i = 0; i<N_Tests; ++i) {
		if (MYTHREAD == 0)
			printf("Starting test %i\n", i);
		for (int j = 0; j < n_iter; j++) {
			if (MYTHREAD == 0)
				begin = clock();
			test_functions[i]();
			if (MYTHREAD == 0) {
				end = clock();
				time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
				time_sum += time_spent;
			}
		}
		if (MYTHREAD == 0) {
			checkTimes(time_spent);
			time_av = time_sum/n_iter;
			printf("Test ended, the results are:\n");

			printf("	Time max = %f\n",time_max);
			printf("	Time min = %f\n",time_min);
			printf("	Time average = %f\n",time_av);
		}
	}

	return 0;
}

void checkTimes(double time_spent) {
	if (time_spent < time_min)
		time_min = time_spent;
	if (time_spent > time_max)
		time_max = time_spent;
}