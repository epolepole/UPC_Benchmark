
#include "bench.h"

int *col_ptr;
int temp;



void init(int argc, const char *argv[]) {

    if (MYTHREAD == 0)
        printf("using %i threads\n", THREADS);
    test_names[0] = "Test 1";
    test_names[1] = "Test 2";
    test_names[2] = "Test 3";
    test_functions[0] = Test1;
    test_functions[1] = Test2;
    test_functions[2] = Test3;
    
    upc_barrier;

    // Static part
    // DEFINITION OF THE MATRICES
    upc_forall(int col = 0; col < THREADS; ++col; col)
    {
        for (int row = 0; row < THREADS; ++row)
        {
            A[row][col] = row + col;
            B[row][col] = 2 * row + col;
        }
    }
    upc_barrier;
    
    // EACH THREAD HAS A PRIVATE POINTER POINING TO EVERY ROW OF 'A'
    for (int row = 0; row < THREADS; ++row)
    {
        row_ptr[row] = &A[row][0];
    }

    upc_barrier;
    //pAB = &AB[0];
    upc_barrier;


    //Dynamic part
    //Allocating




}

// Test1 --> PRIVATE POINTER
void Test1() {
    col_ptr = (int *)&B[0][MYTHREAD];
    
    upc_forall (int i = 0; i < THREADS; ++i; i)     {
        for (int j = 0; j < THREADS; ++j)
        {
            temp = 0;
            
            for (int k = 0; k < THREADS; ++k)
            {
                temp = temp + row_ptr[j][k] * col_ptr[k];
            }
            
            AB[i][j] = temp;
        }	
    }
    upc_barrier;
}

// Test2 --> AFFINITY
void Test2() {
    upc_forall (int i = 0; i < THREADS; ++i; i)     {
        for (int j = 0; j < THREADS; ++j)
        {
            temp = 0;
            
            for (int k = 0; k < THREADS; ++k)
            {
                temp = temp + row_ptr[j][k] * B[k][i];
            }
            
            AB[i][j] = temp;
        }	
    }
    upc_barrier;
}

void Test3() {
    upc_forall (int i = 0; i < THREADS; ++i; i)     {
        for (int j = 0; j < THREADS; ++j)
        {
            temp = 0;
            
            for (int k = 0; k < THREADS; ++k)
            {
                temp = temp + row_ptr[j][k] * B[k][i];
            }
            
            AB[i][j] = temp;
        }   
    }
    upc_barrier;
}