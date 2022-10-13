#ifndef __NUMC_H__
#define __NUMC_H__

#ifndef NCDEF
#define NCDEF
#endif // NCDEF

// includes
#include <string.h>

// Definitions 
// Macros
#define typeof(expr) (_Generic((expr), char: "char", char*: "char*", unsigned char: "unsigned char", signed char: "signed char",short: "short", unsigned short: "unsigned short",int: "int", int*: "int*", unsigned int: "unsigned int",long: "long", unsigned long: "unsigned long",long long: "long long", unsigned long long: "unsigned long long",float: "float",double: "double",long double: "long double",void*: "void*", default: "?")) 
#define ISA(expr, type) (strcmp(typeof(expr), type) == 0)

// Enums
// Structs
//TODO add NCarray struct
// functions


#ifdef NUMC_IMPLEMENTATION
// This is the implementation of the library. It is only included if
// NUMC_IMPLEMENTATION is defined before including the header.

#endif // NUMC_IMPLEMENTATION


// NCarray struct
// This struct contains
// - a pointer to the array
// - the type of the array 
// - the size of the array (int)
// - the shape of the array (which is a pointer to an array of ints)

struct numc_array {
    void* array;
    char* type;
    int size;
    int* shape;
};

// A function that creates a new NCarray struct
// It takes a pointer to an array, the type of the array, the size of the array, and the shape of the array
// It returns a pointer to the new NCarray struct
struct numc_array* new_numc_array(void* array, char* type, int size, int* shape) {
    struct numc_array* new_array = malloc(sizeof(struct numc_array));
    new_array->array = array;
    new_array->type = type;
    new_array->size = size;
    new_array->shape = shape;
    return new_array;
}





#endif  // __NUMC_H__