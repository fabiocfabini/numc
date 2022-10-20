#include <stdio.h>
#include "../includes/test.h"

//NOTE: Testing system could probably be improved by using a testing framework or by using Python to run the tests
int main(){
    int total = 0;
    int passed = 0;
    int failed = 0;

    if(total == 0){
        printf("No tests to run.\n");
        return 0;
    }else{
        printf("[INFO] STARTED TESTS\n");

        printf("[INFO] REPORT: %d/ %d tests passed (%f%%). Failed %d.\n", passed, total, passed/total * 100.0, failed);
    }

    return 0;
}

