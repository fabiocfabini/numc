#include <stdio.h>
#include "../includes/test.h"

int main(){
    int total = 0;
    int passed = 0;
    int failed = 0;

    printf("[INFO] STARTED TESTS\n");

    test_typecheck(&total, &passed, &failed);

    printf("[INFO] REPORT: %d/%d tests passed.\n", passed, total);
}
