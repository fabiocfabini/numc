#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "../includes/numc.h"


int nc_equal(NCarray arr1, NCarray arr2){
    int equal = 1;

    // Check for valid arrays
    if(arr1 == NULL || arr2 == NULL){
        fprintf(stderr, "Error in nc_equal: One of the arrays is NULL! &arr1 = %p, &arr2 = %p\n", (void*)arr1, (void*)arr2);
        exit(EXIT_FAILURE);
    }

    // Check for equal length
    if(arr1->length != arr2->length){
        fprintf(stderr, "Could not compare arrays due to unequal length (%d != %d)", arr1->length, arr2->length);
        exit(EXIT_FAILURE);
    }

    // Check for equal type
    if(strcmp(arr1->type, arr2->type) != 0){
        fprintf(stderr, "Could not compare arrays due to unequal type (%s != %s)", arr1->type, arr2->type);
        exit(EXIT_FAILURE);
    }

    // Check for equal shapes
    if(arr1->ndim != arr2->ndim || memcmp(arr1->shape, arr2->shape, arr1->ndim * sizeof(short int)) != 0){
        fprintf(stderr, "Could not compare arrays due to unequal dimensions (%d != %d)", arr1->ndim, arr2->ndim);
        exit(EXIT_FAILURE);
    }

    // Check for equal data
    if(strcmp(arr1->type, "i32") == 0){
        if(memcmp(arr1->data, arr2->data, arr1->length * sizeof(float)) != 0) equal = 0;
    }else if(strcmp(arr1->type, "f32") == 0){
        if(memcmp(arr1->data, arr2->data, arr1->length * sizeof(float)) != 0) equal = 0;
    }else{
        fprintf(stderr, "Error in nc_cmp: type %s is not supported!\n", arr1->type);
        exit(EXIT_FAILURE);
    }
    return equal;
}