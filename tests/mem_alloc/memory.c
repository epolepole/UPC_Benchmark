#include "memory.h"



int main(int argc, char const *argv[])
{
	int SIZE;
	int option_user;

	if (argc!=2) {
		SIZE = THREADS;
	}

	//Size = N * T if BF <= N affinity
	else {
		SIZE = atoi(argv[1]);
	}

	//static shared int A[THREADS][THREADS], B[THREADS][THREADS], AB[THREADS][THREADS];
	shared [BLOCKING_FACTOR] int* A;
	shared [BLOCKING_FACTOR] int* B;
	shared [BLOCKING_FACTOR] int* AB;

	int n_blocks;

	n_blocks = SIZE*SIZE/BLOCKING_FACTOR;

	initialization(&A, &B, &AB, n_blocks, SIZE);
	upc_barrier;
	multiplication(A, B,  AB, SIZE);
	upc_barrier;
	print(A, B, AB, SIZE);
	upc_barrier;

	if(MYTHREAD == 0)
	{
		upc_free(A);
		upc_free(B);
		upc_free(AB);
	}

	/*
	| 0  1  2  3 |  | 0  1  2  3 |   =   | 28  34  40  46 |
	| 1  2  3  4 |  | 2  3  4  5 |   =   | 40  50  60  70 |
	| 2  3  4  5 |  | 4  5  6  7 |   =   | 52  66  80  94 |
	| 3  4  5  6 |  | 6  7  8  9 |   =   | 64  82  100 118|
	*/

	return 0;
}

void initialization (shared [BLOCKING_FACTOR] int* *A, shared [BLOCKING_FACTOR] int* *B, shared [BLOCKING_FACTOR] int* *AB, int n_blocks, int SIZE)
{
	int row, col;

	// DYANMIC ALLOCATION OF THE MATRICES AND THE ARRAY OF POINTERS
	*A = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, n_blocks*sizeof(int));
	*B = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, n_blocks*sizeof(int));
	*AB = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, n_blocks*sizeof(int));

	// DEFINITION OF THE MATRICES
	upc_forall(col = 0; col < SIZE; ++col; col)
	{
		for (row = 0; row < SIZE; ++row)
		{
			(*A)[row * SIZE + col] = row + col;
			(*B)[row * SIZE + col] = 2 * row + col;
		}
	}
	printf("Matrices initialized\n");
}

void multiplication(shared [BLOCKING_FACTOR] int* A, shared [BLOCKING_FACTOR] int* B, shared [BLOCKING_FACTOR] int* AB, int SIZE)
{
	int i, j, k, temp;
	printf("Entering multiplication\n");
	// MULTIPLICATION
	upc_forall (i = 0; i < SIZE; ++i; i) // MOVEMENT IN COLUMNS (MATRIX 'AB')
	{
		for (j = 0; j < SIZE; ++j) // MOVEMENT IN ROWS (MATRIX 'AB')
		{
			temp = 0;

			for (k = 0; k < SIZE; ++k)
			{
				temp = temp + A[j * SIZE + k] * B[k * SIZE + i];
			}

			AB[j * SIZE + i] = temp;
		}	
	}
	printf("Exiting multiplication\n");
}

void print(shared [BLOCKING_FACTOR] int* A, shared [BLOCKING_FACTOR] int* B, shared [BLOCKING_FACTOR] int* AB, int SIZE)
{
	int row, col;

	if (MYTHREAD == 0)
	{
		printf("The result of the operation A * B = AB is:\n\n");
		for (row = 0; row < SIZE; ++row)
		{
			printf("|");

			for (col = 0; col < SIZE; ++col)
			{
				printf(" %i ", A[row * SIZE + col]);
			}

			printf("|  ");
			printf("|");

			for (col = 0; col < SIZE; ++col)
			{
				printf(" %i ", B[row * SIZE + col]);
			}

			printf("|\t");
			printf("|");

			for (col = 0; col < SIZE; ++col)
			{
				printf(" %i ", AB[row * SIZE + col]);
			}
			printf("|\n");
		}
	}
}
