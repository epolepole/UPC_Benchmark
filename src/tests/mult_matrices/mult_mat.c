
#include "mult_mat.h"
#include "T.h"

int temp;

void adding_names() {
    upc_barrier;
    test_names[0] = "Shared memory, accessed with private to shared pointers. Full matrix pointer for B";
    test_names[1] = "Shared memory, accessed with private to shared pointers. Single column pointer for B";
    test_names[2] = "Shared memory, accessed with array";
    test_names[3] = "Local memory";
    test_names[4] = "Dynamic shared allocation, accessed with array";
}

void adding_tests() {    
    upc_barrier;
    test_functions[0] = Test1;
    test_functions[1] = Test2;
    test_functions[2] = Test3;
    test_functions[3] = Test4;
    test_functions[4] = Test5;
}

void init(int argc, const char *argv[]) {

    n_blocks = SIZE*SIZE/BLOCKING_FACTOR;

    if (MYTHREAD == 0){
        printf("using %i threads\n\n", THREADS);
        printf("Matrix size = %i x %i\n",SIZE, SIZE);
    }

    adding_names();
    adding_tests();    

    //Dynamic allocation
    dynamic_allocation();

    // DEFINITION OF THE MATRICES    
    shared_definition();
    local_definition();
    dynamic_definiton();

      
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

void end_test() {
    upc_barrier;   
    free_allocation(); 
    upc_barrier;   
}



void shared_definition() {
    // Shared definition
    upc_barrier;
    upc_forall(int col = 0; col < SIZE; ++col; col)
    {
        for (int row = 0; row < SIZE; ++row)
        {
            A[row][col] = row + col;
            B[row][col] = 2 * row + col;
        }
    }
}

void local_definition() {
    //Local definition
    upc_barrier;
    for(int col = 0; col < SIZE; ++col)
    {
        for (int row = 0; row < SIZE; ++row)
        {
            A_local[row][col] = A[row][col];
            B_local[row][col] = B[row][col];
        }
    }
}

void dynamic_allocation() {
    //Dynamic allocation
    upc_barrier;
    dA = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, n_blocks*sizeof(int));
    dB = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, n_blocks*sizeof(int));
    dAB = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, n_blocks*sizeof(int));

}

void free_allocation() {
    upc_barrier;
    if(MYTHREAD == 0)
    {
        upc_free(dA);
        upc_free(dB);
        upc_free(dAB);
    }
}

void dynamic_definiton() {
    upc_barrier;
    upc_forall(int col = 0; col < SIZE; ++col; col)
    {
        for (int row = 0; row < SIZE; ++row)
        {
            dA[row * SIZE + col] = row + col;
            dB[row * SIZE + col] = 2 * row + col;
        }
    }  
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
            AB[i][j] = temp;
        }   
    }
    upc_barrier;
}

void Test5() {
    upc_forall (int i = 0; i < SIZE; ++i; i) // MOVEMENT IN COLUMNS (MATRIX 'AB')
    {
        for (int j = 0; j < SIZE; ++j) // MOVEMENT IN ROWS (MATRIX 'AB')
        {
            temp = 0;

            for (int k = 0; k < SIZE; ++k)
            {
                temp = temp + dA[j * SIZE + k] * dB[k * SIZE + i];
            }

            dAB[j * SIZE + i] = temp;
        }   
    }
    upc_barrier;

    
}
