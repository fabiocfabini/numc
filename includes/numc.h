#ifndef __NUMC_H__
#define __NUMC_H__

#ifndef NCDEF
#define NCDEF
#endif // NCDEF

#include <string.h>


#define MAX_TYPE_LEN 5

#define typeof(expr) (_Generic((expr), char: "char", char*: "char*", unsigned char: "unsigned char", signed char: "signed char",short: "short", unsigned short: "unsigned short",int: "int", int*: "int*", unsigned int: "unsigned int",long: "long", unsigned long: "unsigned long",long long: "long long", unsigned long long: "unsigned long long",float: "float",double: "double",long double: "long double",void*: "void*", default: "?")) 
#define ISA(expr, type) (strcmp(typeof(expr), type) == 0)


typedef struct nc_array{
    int length;
    void* data;
    short int ndim;
    short int* shape;
    char type[MAX_TYPE_LEN];
} *NCarray, **NCtable;

/**
 * @brief Frees the memory allocated for an NCarray
 * 
 * @param arr The NCarray to free
 */
void nc_free_array(NCarray arr);

/**
 * @brief Initializes an NCarray with default values
 * 
 * @return NCarray The initialized NCarray
 */
NCarray nc_init_array();

/**
 * @brief Creates an NCarray with all values set to 0
 * 
 * @param type The type of the array
 * @param ndim The number of dimensions of the array
 * @param ... The size of each dimension. Must be ndim arguments
 * @return NCarray The initialized NCarray
 */
NCarray nc_zeros(const char* type, short int ndim, ...);

/**
 * @brief Creates an NCarray with all values set to 1
 * 
 * @param type The type of the array
 * @param ndim The number of dimensions of the array
 * @param ... The size of each dimension. Must be ndim arguments
 * @return NCarray The initialized NCarray
 */
NCarray nc_ones(const char* type, short int ndim, ...);









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