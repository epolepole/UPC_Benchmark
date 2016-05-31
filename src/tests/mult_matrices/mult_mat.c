
#include "mult_mat.h"
#include "T.h"

int temp;

void init(int argc, const char *argv[]) {

    if (MYTHREAD == 0){
        printf("using %i threads\n\n", THREADS);
        printf("Matrix size = %i x %i\n",SIZE, SIZE);
    }

    test_names[0] = "Shared memory, accessed with private to shared pointers\n Full matrix pointer for B";
    test_names[1] = "Shared memory, accessed with private to shared pointers\n Single column pointer for B";
    test_names[2] = "Shared memory, accessed with array";
    test_names[3] = "Local memory";
    test_functions[0] = Test1;
    test_functions[1] = Test2;
    test_functions[2] = Test3;
    test_functions[3] = Test4;
    
    upc_barrier;

    // DEFINITION OF THE MATRICES
    // Shared definition
    upc_forall(int col = 0; col < SIZE; ++col; col)
    {
        for (int row = 0; row < SIZE; ++row)
        {
            A[row][col] = row + col;
            B[row][col] = 2 * row + col;
        }
    }
    upc_barrier;

    //Local definition
    for(int col = 0; col < SIZE; ++col)
    {
        for (int row = 0; row < SIZE; ++row)
        {
            A_local[row][col] = A[row][col];
            B_local[row][col] = B[row][col];
        }
    }
    upc_barrier;
    
    // EACH THREAD HAS A PRIVATE POINTER POINING TO EVERY ROW OF 'A'
    for (int row = 0; row < SIZE; ++row)
    {
        row_ptr[row] = &A[row][0];
    }
    upc_barrier;

    col_ptr = (int *)&B[0][MYTHREAD];

    upc_barrier;
    pB = &B[0][0];
    pAB = &AB[0][0];
    upc_barrier;
}

void Test1() {
    
    upc_forall (int j = 0; j < SIZE; ++j; j)     {
        for (int i = 0; i < SIZE; ++i)
        {
            temp = 0;
            
            for (int k = 0; k < SIZE; ++k)
            {
                temp = temp + row_ptr[i][k] * pB[k*SIZE + j];
            }
            
            pAB[i*SIZE + j] = temp;
        }	
    }
    upc_barrier;
}

void Test2() {
    
    upc_forall (int j = 0; j < SIZE; ++j; j)     {
        for (int i = 0; i < SIZE; ++i)
        {
            temp = 0;
            
            for (int k = 0; k < SIZE; ++k)
            {
                temp = temp + row_ptr[i][k] * col_ptr[((j-j%THREADS)/THREADS)%MULTIPLICATION_FACTOR + k];
                
            }
            
            pAB[i*SIZE + j] = temp;
        }   
    }
    upc_barrier;
}

void Test3() {
    upc_forall (int j = 0; j < SIZE; ++j; j)     {
        for (int i = 0; i < SIZE; ++i)
        {
            temp = 0;
            
            for (int k = 0; k < SIZE; ++k)
            {
                temp = temp + A[i][k] * B[k][j];
            }
            
            AB[i][j] = temp;
        }	
    }
    upc_barrier;
}

void Test4() {
    upc_forall (int j = 0; j < SIZE; ++j; j)     {
        for (int i = 0; i < SIZE; ++i)
        {
            temp = 0;
            
            for (int k = 0; k < SIZE; ++k)
            {
                temp = temp + A_local[i][k] * B_local[k][j];
            }

            AB_local[i][j] = temp;
        }   
    }
    upc_barrier;
}