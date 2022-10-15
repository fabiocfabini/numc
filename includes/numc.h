#ifndef __NUMC_H__
#define __NUMC_H__

#ifndef NCDEF
#define NCDEF
#endif // NCDEF

#include <string.h>


#define MAX_TYPE_LEN 5
#define NC_TABLE_CAP 10

#define FFMT "%*.*f"

#define typeof(expr) (_Generic((expr), char: "char", char*: "char*", unsigned char: "unsigned char", signed char: "signed char",short: "short", unsigned short: "unsigned short",int: "int", int*: "int*", unsigned int: "unsigned int",long: "long", unsigned long: "unsigned long",long long: "long long", unsigned long long: "unsigned long long",float: "float",double: "double",long double: "long double",void*: "void*", default: "?")) 
#define ISA(expr, type) (strcmp(typeof(expr), type) == 0)

//NOTE: Discuss if having seperate structs for each type is better
typedef struct nc_array{
    void* data;
    int length;
    // void* data;
    int ndim;
    int* shape;
    char type[MAX_TYPE_LEN];
} *NCarray;

extern size_t nc_count;
extern size_t data_count;
extern NCarray NC_TABLE[NC_TABLE_CAP];
extern void* DATA_TABLE[NC_TABLE_CAP];

/**
 * @brief Frees the memory allocated for an NCarray
 * 
 * @param arr The NCarray to free
 */
void nc_free_array(NCarray arr);

/**
 * @brief Frees the memory allocated for all NCarrays
 *      Calling this function is optional, as the memory will be freed
 *     when the program exits.
 *
 */
void nc_collect();

/**
 * @brief Initializes an NCarray with default values
 * 
 * @return NCarray The initialized NCarray
 */
NCarray nc_init_array();

/**
 * @brief Compares two NCarrays
 * 
 * @param arr1 The first NCarray
 * @param arr2 The second NCarray
 * @return return enum from NC_CMP_STATUS 
 */
int nc_equal(NCarray arr1, NCarray arr2);

/**
 * @brief Prints an NCarray to stdout
 * 
 * @param arr The NCarray to print
 * @param width The width of each column
 * @param precision The precision of each element
 */
void nc_show(NCarray arr, int width, int precision); //TODO: Make formatting adjust automatically (without width)

/**
 * @brief Creates an NCarray with a given shape and type and fills it with 0s
 * 
 * @param type The type of the array
 * @param ndim The number of dimensions of the array
 * @param ... The size of each dimension. Must be ndim arguments
 * @return NCarray The initialized NCarray
 */
NCarray nc_zeros(const char* type, int ndim, ...);

/**
 * @brief Creates an NCarray with a given shape and type and fills it with 1s
 * 
 * @param type The type of the array
 * @param ndim The number of dimensions of the array
 * @param ... The size of each dimension. Must be ndim arguments
 * @return NCarray The initialized NCarray
 */
NCarray nc_ones(const char* type, int ndim, ...);

/**
 * @brief Creates an NCarray with a given shape and type and fills it with the `fill_value`
 * 
 * @param type The type of the array
 * @param fill_value The value to fill the array with
 * @param ndim The number of dimensions of the array
 * @param ... The size of each dimension. Must be ndim arguments
 * @return The initialized NCarray
 */
NCarray nc_fill(const char* type, void* fill_value, int ndim, ...);

/**
 * @brief Creates an NCarray with evenly spaced values between start and stop
 * 
 * @param type The type of the array
 * @param start The start value
 * @param stop The stop value
 * @param step The step size
 * @return NCarray ranging [start, stop, step]
 */
NCarray nc_arange(const char* type, int start, int stop, int step);

/**
 * @brief Reshapes an NCarray maintaining the same data
 * 
 * @param arr The NCarray to reshape
 * @param new_shape_dim The new number of dimensions
 * @param ... The new size of each dimension. Must be ndim arguments
 * @return The reshaped NCarray.
 */
NCarray nc_reshape(const NCarray arr, int new_shape_dim, ...);






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
//NOTE: Talk to Miguel about implementation
// struct numc_array {
//     void* array;
//     char* type;
//     int size;
//     int* shape;
// };

// // A function that creates a new NCarray struct
// // It takes a pointer to an array, the type of the array, the size of the array, and the shape of the array
// // It returns a pointer to the new NCarray struct
// struct numc_array* new_numc_array(void* array, char* type, int size, int* shape) {
//     struct numc_array* new_array = malloc(sizeof(struct numc_array));
//     new_array->array = array;
//     new_array->type = type;
//     new_array->size = size;
//     new_array->shape = shape;
//     return new_array;
// }





#endif  // __NUMC_H__