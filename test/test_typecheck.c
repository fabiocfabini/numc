#include <stdio.h>
#include <assert.h>
#include "../includes/numc.h"

void test_typecheck(int* total, int* passed, int* failed){
    const int NUM_TESTS = 12;
    int i = 1;
    char c = 'a';
    float f = 1.0;
    double d = 1.0;
    short sh = 1;
    long l = 1;
    long long ll = 1;
    int* ip = &i;
    char* s = "hello";
    void* p = NULL;
    unsigned int ui = 1;
    unsigned short us = 1;

    //TODO: Add  typecheck for NCarray once the struct is defined
    printf("\t[INFO] STARTED TYPECHECK TESTS\n");
    ISA(i, "int")             ? (*passed)++: printf("\t\t[ERROR] FAILED INT TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(c, "char")            ? (*passed)++: printf("\t\t[ERROR] FAILED CHAR TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(f, "float")           ? (*passed)++: printf("\t\t[ERROR] FAILED FLOAT TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(d, "double")          ? (*passed)++: printf("\t\t[ERROR] FAILED DOUBLE TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(sh, "short")          ? (*passed)++: printf("\t\t[ERROR] FAILED SHORT TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(l, "long")            ? (*passed)++: printf("\t\t[ERROR] FAILED LONG TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(ll, "long long")      ? (*passed)++: printf("\t\t[ERROR] FAILED LONG LONG TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(ip, "int*")           ? (*passed)++: printf("\t\t[ERROR] FAILED INT* TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(s, "char*")           ? (*passed)++: printf("\t\t[ERROR] FAILED CHAR* TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(p, "void*")           ? (*passed)++: printf("\t\t[ERROR] FAILED VOID* TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(ui, "unsigned int")   ? (*passed)++: printf("\t\t[ERROR] FAILED UNSIGNED INT TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    ISA(us, "unsigned short") ? (*passed)++: printf("\t\t[ERROR] FAILED UNSIGNED SHORT TYPECHECK TEST %d.\n", *total + *passed + ++(*failed));
    
    assert(*passed + *failed == NUM_TESTS && "Non exhaustive typecheck tests\n");
    *total += *passed + *failed;
}