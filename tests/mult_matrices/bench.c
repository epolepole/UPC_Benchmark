
#include "bench.h"

int *col_ptr;
int temp;
int row, col, i, j, k;




void init() {

    test_functions[0] = Test1;
    test_functions[1] = Test2;
    
    upc_barrier;


    // DEFINITION OF THE MATRICES
    upc_forall(col = 0; col < THREADS; ++col; col)
    {
        for (row = 0; row < THREADS; ++row)
        {
            A[row][col] = row + col;
            B[row][col] = 2 * row + col;
        }
    }
    upc_barrier;
    
    // EACH THREAD HAS A PRIVATE POINTER POINING TO EVERY ROW OF 'A'
    for (row = 0; row < THREADS; ++row)
    {
        row_ptr[row] = &A[row][0];
    }
    upc_barrier;
}

// Test1 --> PRIVATE POINTER
void Test1()
{
    col_ptr = (int *)&B[0][MYTHREAD];
    
    upc_forall (i = 0; i < THREADS; ++i; i)     {
        for (j = 0; j < THREADS; ++j)
        {
            temp = 0;
            
            for (k = 0; k < THREADS; ++k)
            {
                /*
                printf("Fron thread %i,i=%i j=%i, k=%i\n", MYTHREAD, i, j, k);
                
                printf("Col ptr value: %i\n", *(col_ptr + k));
                printf("Row ptr value: %i\n", *(row_ptr[j] + k) );
                */
                temp = temp + row_ptr[j][k] * col_ptr[k];
            }
            
            AB[j][i] = temp;
        }	
    }
    upc_barrier;
}

// Test2 --> AFFINITY
void Test2()
{
    upc_forall (i = 0; i < THREADS; ++i; i)     {
        for (j = 0; j < THREADS; ++j)
        {
            temp = 0;
            
            for (k = 0; k < THREADS; ++k)
            {
                temp = temp + *(row_ptr[j] + k) * B[k][i];
            }
            
            AB[j][i] = temp;
        }	
    }
    upc_barrier;
}