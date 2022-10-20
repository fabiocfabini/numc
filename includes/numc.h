#ifndef __NUMC_H__
#define __NUMC_H__

#ifndef NCDEF
#define NCDEF
#endif // NCDEF

#include <string.h>


#define MAX_TYPE_LEN 5
#define NC_TABLE_CAP 10

#define NC_INT "i32"
#define NC_FLOAT "f32"

#define FFMT "%*.*f"

#define typeof(expr) (_Generic((expr), char: "char", char*: "char*", unsigned char: "unsigned char", signed char: "signed char",short: "short", unsigned short: "unsigned short",int: "int", int*: "int*", unsigned int: "unsigned int",long: "long", unsigned long: "unsigned long",long long: "long long", unsigned long long: "unsigned long long",float: "float",double: "double",long double: "long double",void*: "void*", default: "?")) 
#define ISA(expr, type) (strcmp(typeof(expr), type) == 0)

//NOTE: Discuss if having seperate structs for each type is better
typedef struct nc_array{
    void* data;
    int length, ndim;
    int *shape;
    char type[MAX_TYPE_LEN];
} *NCarray;

//NOTE: Thougths on freeing the memory allocated for the array?
/*
The optimal way to free the memory allocated for the nc_arrays is to have them in a hash table and free them when the program exits.
The hash table would allow or users to free the memory allocated for the arrays manually if they want to and still call nc_collect()
at the end of the program to free the memory allocated for the arrays that were not freed manually.
This would require each struct to have certain identifiers that would allow the hash table to find the struct in the table.
Maybe an array of random characters that are generated when the struct is created and are used to find the struct in the hash table.
How would this work for NCarrays that share the same data? Maybe having 2 hash tables, one for the data and one for the structs?

An easier way to free the memory would be to store the pointers to the data in a linked list and free them when the program exits.
This option is not as good as the previous one because it would not allow the user to free the memory allocated for the arrays manually.
*/
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
 * @brief Frees the memory allocated for all NCarrays.
 *      Calling this function is optional but it is recommended to call it at the end of the program.
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

//TODO: Make formatting adjust automatically (without width)
//IDEA: Printing big arrays should be done in a different way. By default, only the first and last x elements should be printed
/**
 * @brief Prints an NCarray to stdout
 * 
 * @param arr The NCarray to print
 * @param width The width of each column
 * @param precision The precision of each element
 */
void nc_show(NCarray arr, int width, int precision);

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

/**
 * @brief Copies an NCarray
 * 
 * @param src The NCarray to copy
 * @return The copied NCarray
 */
NCarray nc_copy(NCarray src);

/**
 * @brief Saves an NCarray to a file
 * 
 * @param arr The NCarray to save
 * @param filename The name or path of the file to save to
 */
void nc_save(NCarray arr, const char* filename);

/**
 * @brief Loads an NCarray from a file
 * 
 * @param filename The name or path of the file to load from
 * @return The loaded NCarray
 */
NCarray nc_load(const char* filename);





#ifdef NUMC_IMPLEMENTATION
// This is the implementation of the library. It is only included if
// NUMC_IMPLEMENTATION is defined before including the header.

#endif // NUMC_IMPLEMENTATION

#endif  // __NUMC_H__