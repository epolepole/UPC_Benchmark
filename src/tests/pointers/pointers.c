
#include "pointers.h"
#include "T.h"


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


}



// Test1 --> PRIVATE POINTER
void Test1() {
        
}

// Test2 --> AFFINITY
void Test2() {
    
}

void Test3() {
    
}
