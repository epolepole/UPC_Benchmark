
#include "affvt.h"
#include "T.h"

int temp;

void adding_names() {
    upc_barrier;
    for(int i=0; i<N_Tests; i++) {
        test_names[i] = (char *) malloc(50*sizeof(char));
    }
    sprintf(test_names[0], "Shared memory, threads = size          = %i", SIZE);
    sprintf(test_names[1], "Local memory,  threads = size          = %i", SIZE);
    sprintf(test_names[2], "Local memory,  threads = 0.85 * size   = %i", (int) (0.85 * SIZE));
    sprintf(test_names[3], "Local memory,  threads = 0.75 * size   = %i", (int) (0.75 * SIZE));
    sprintf(test_names[4], "Local memory,  threads = 0.66 * size   = %i", (int) (0.66 * SIZE));
    sprintf(test_names[5], "Local memory,  threads = 0.50 * size   = %i", (int) (0.5 * SIZE));
    sprintf(test_names[6], "Local memory,  threads = 0.40 * size   = %i", (int) (0.4 * SIZE));
}



void adding_tests() {    
    upc_barrier;
    test_functions[0] = Test1;
    test_functions[1] = Test2;
    test_functions[2] = Test3;
    test_functions[3] = Test4;
    test_functions[4] = Test4;
    test_functions[5] = Test4;
    test_functions[6] = Test4;
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
    local_definition();
    dynamic_definiton();

      
    upc_barrier;  
    
}

void end_test() {
    upc_barrier;   
    free_allocation(); 
    upc_barrier;   
}


void dynamic_allocation() {
    //Dynamic allocation
    upc_barrier;
    dA = (shared [SIZE] int*) upc_all_alloc(SIZE, SIZE*sizeof(int));
    dB = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, BLOCKING_FACTOR*sizeof(int));
    dAB = (shared [BLOCKING_FACTOR] int*) upc_all_alloc(n_blocks, BLOCKING_FACTOR*sizeof(int));
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


void local_definition() {
    
    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            lA[row][col] = row + col;
            lB[row][col] = 2 * row + col;
        }
    }



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


void multiplication_shared(shared [SIZE] int* A, shared [BLOCKING_FACTOR] int* B, shared [BLOCKING_FACTOR] int* AB) {
    int i, j, k, temp;

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

}


void multiplication_local(int A[][], int B[][], shared [BLOCKING_FACTOR] int* pAB, int actual_threads)
{
    int i, j, k, temp;
    int result[SIZE];
    // MULTIPLICATION
    upc_forall (i = 0; i < SIZE; ++i; i%actual_threads) // MOVEMENT IN COLUMNS (MATRIX 'AB')
    {
        //printf("Using thread %i\n",MYTHREAD);
        for (j = 0; j < SIZE; ++j) // MOVEMENT IN ROWS (MATRIX 'AB')
        {
            temp = 0;

            for (k = 0; k < SIZE; ++k)
            {
                temp = temp + A[j][k] * B[k][i];
            }
            result[j] = temp;

        }  
        upc_memput(&pAB[i*SIZE],result,SIZE*sizeof(int));
    }
}

void Test1() {
    multiplication_shared(dA, dB, dAB);
}

void Test2() {
    actual_threads = THREADS;    
    multiplication_local(lA, lB, dAB, actual_threads);
}

void Test3() {
    actual_threads = (int) (0.85 * THREADS);    
    multiplication_local(lA, lB, dAB, actual_threads);
}

void Test4() {
    actual_threads = (int) (0.75 * THREADS);    
    multiplication_local(lA, lB, dAB, actual_threads);
}

void Test5() {
    actual_threads = (int) (0.66 * THREADS);    
    multiplication_local(lA, lB, dAB, actual_threads);
}

void Test6() {
    actual_threads = (int) (0.5 * THREADS);    
    multiplication_local(lA, lB, dAB, actual_threads);
}

void Test7() {
    actual_threads = (int) (0.4 * THREADS);    
    multiplication_local(lA, lB, dAB, actual_threads);
}
