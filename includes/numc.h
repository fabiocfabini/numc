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
// functions


#ifdef NUMC_IMPLEMENTATION
// This is the implementation of the library. It is only included if
// NUMC_IMPLEMENTATION is defined before including the header.

#endif // NUMC_IMPLEMENTATION

#endif  // __NUMC_H__