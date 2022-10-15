#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../includes/numc.h"


NCarray nc_zeros(const char* type, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "Error in nc_zeros: Could not allocate memory for NCarray!\n");
        return NULL;
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    va_list args;
    va_start(args, ndim);

    if(ndim <= 0){
        fprintf(stderr, "Error in nc_zeros: ndim must be greater than 0!\n");
        goto error;
    }
    arr->ndim = ndim;
    arr->length = 1;

    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    for(short int i = 0; i < arr->ndim; i++){
        arr->shape[i] = va_arg(args, int);
        arr->length *= arr->shape[i];
    }

    //Set all the values to 0
    if(strcmp(type, "i32") == 0){
        arr->data = (int*) calloc(arr->length, sizeof(int));
    }else if(strcmp(type, "f32") == 0){
        arr->data = (float*) calloc(arr->length, sizeof(float));
    }else{
        fprintf(stderr, "Error in nc_zeros: type %s is not supported!\n", type);
        goto error;
    }

    return arr;

error:
    nc_collect();
    exit(EXIT_FAILURE);
}

NCarray nc_ones(const char* type, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "Error in nc_ones: Could not allocate memory for NCarray!\n");
        return NULL;
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    va_list args;
    va_start(args, ndim);

    if(ndim <= 0){
        fprintf(stderr, "Error in nc_ones: ndim must be greater than 0!\n");
        goto error;
    }
    arr->ndim = ndim;
    arr->length = 1;

    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    for(short int i = 0; i < arr->ndim; i++){
        arr->shape[i] = va_arg(args, int);
        arr->length *= arr->shape[i];
    }

    //Set all the values to 0
    if(strcmp(type, "i32") == 0){
        arr->data = (int*) calloc(arr->length, sizeof(int));
        for(int i = 0; i < arr->length; i++){
            ((int*)arr->data)[i] = 1;
        }
    }else if(strcmp(type, "f32") == 0){
        arr->data = (float*) calloc(arr->length, sizeof(float));
        for(int i = 0; i < arr->length; i++){
            ((float*)arr->data)[i] = 1.0f;
        }
    }else{
        fprintf(stderr, "Error in nc_ones: type %s is not supported!\n", type);
        goto error;
    }

    return arr;

error:
    nc_collect();
    exit(EXIT_FAILURE);
}