#include "T.h"
#include <time.h>
#include <float.h>
#include <upc.h>

//http://stackoverflow.com/questions/5248915/execution-time-of-c-program
shared clock_t begin, end;
shared double time_spent;
time_t timer;
char buffer[26];
struct tm* tm_info; 

static shared double time_min = DBL_MAX;
static shared double time_max = 0;
static shared double time_av = 0;
static shared double time_sum = 0;

static shared int n_iter = 1000;

void checkTimes(double time_spent);


int main(int argc, const char * argv[]) {
	
	if (MYTHREAD == 0) {
		if (argc == 2)
			n_iter = atoi(argv[1]);	
		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer , 26 , "%Y:%m:%d %H:%M:%S", tm_info);

		printf("\n\n\n*************************************************************************\n");
		printf("\n Time: %s\n\n",buffer);
		printf("\n\n\n\
			*****************************************************\n\
			*                                                   *\n\
			*                   Testing TIME!                   *\n\
			*                                                   *\n\
			*****************************************************\n\n\n");
		printf("Runing %i iterations per test\n\n",n_iter);
	}

	upc_barrier;
	init(2,NULL);
	upc_barrier;

	for (int i = 0; i<N_Tests; ++i) {

		if (MYTHREAD == 0){
			//printf("\n    ***Starting test %i***\n", i);
			printf("\n%s\n\n",test_names[i]);
			time_min = DBL_MAX;
			time_max = 0;
			time_av = 0;
			time_sum = 0;
		}
		upc_barrier;

		for (int j = 0; j < n_iter; j++) {


			if (MYTHREAD == 0) {
				//printf("Begin iteration number %i\n", j);
				begin = clock();
			}
			upc_barrier;

			test_functions[i]();

			upc_barrier;

			if (MYTHREAD == 0) {
				end = clock();
				time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
				time_sum += time_spent;
				checkTimes(time_spent);
			}
			upc_barrier;
		}

		if (MYTHREAD == 0) {

			time_av = time_sum/n_iter;
			//printf("Test ended, the results are:\n");

			printf("	Time max = %f\n",time_max);
			printf("	Time min = %f\n",time_min);
			printf("	Time average = %f\n",time_av);
		}
		upc_barrier;
	}

	upc_barrier;
	end_test();
	upc_barrier;

	return 0;
}

void checkTimes(double time_spent) {
	if (time_spent < time_min)
		time_min = time_spent;
	if (time_spent > time_max)
		time_max = time_spent;
}