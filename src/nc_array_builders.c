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
        goto error;
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
    }DATA_TABLE[data_count++] = arr->data;


    return arr;

error:
    nc_collect();
    exit(EXIT_FAILURE);
}

NCarray nc_ones(const char* type, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "Error in nc_ones: Could not allocate new NCarray!\n");
        goto error;
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

    //Set all the values to 1
    if(strcmp(type, "i32") == 0){
        arr->data = (int*) calloc(arr->length, sizeof(int));
        for(int i = 0; i < arr->length; i++){
            ((int*) arr->data)[i] = 1;
        }
    }else if(strcmp(type, "f32") == 0){
        arr->data = (float*) calloc(arr->length, sizeof(float));
        for(int i = 0; i < arr->length; i++){
            ((float*) arr->data)[i] = 1;
        }
    }else{
        fprintf(stderr, "Error in nc_ones: type %s is not supported!\n", type);
        goto error;
    }DATA_TABLE[data_count++] = arr->data;

    return arr;

error:
    nc_collect();
    exit(EXIT_FAILURE);
}

NCarray nc_arange(const char* type, int start, int stop, int step){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "Error in nc_arange: Could not allocate new NCarray!\n");
        goto error;
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    arr->ndim = 1;
    arr->length = (stop - start) / step;
    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    arr->shape[0] = arr->length;

    //Set all the values to 0
    if(strcmp(type, "i32") == 0){
        arr->data = (int*) malloc(sizeof(int) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((int*) arr->data)[i] = start + i * step;
        }
    }else if(strcmp(type, "f32") == 0){
         arr->data = (float*) malloc(sizeof(float) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((float*) arr->data)[i] = (float)start + (float)i * (float)step;
        }
    }else{
        fprintf(stderr, "Error in nc_arange: type %s is not supported!\n", type);
        goto error;
    }DATA_TABLE[data_count++] = arr->data;

    return arr;

    error:
        nc_collect();
        exit(EXIT_FAILURE);
}

NCarray nc_fill(const char* type, void* fill_value, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "Error in nc_fill: Could not allocate new NCarray!\n");
        goto error;
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    va_list args;
    va_start(args, ndim);

    if(ndim <= 0){
        fprintf(stderr, "Error in nc_fill: ndim must be greater than 0!\n");
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
        arr->data = (int*) malloc(sizeof(int) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((int*) arr->data)[i] = *((int*) fill_value);
        }
    }else if(strcmp(type, "f32") == 0){
        arr->data = (float*) malloc(sizeof(float) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((float*) arr->data)[i] = *((float*) fill_value);
        }
    }else{
        fprintf(stderr, "Error in nc_fill: type %s is not supported!\n", type);
        goto error;
    }DATA_TABLE[data_count++] = arr->data;

    return arr;

    error:
        nc_collect();
        exit(EXIT_FAILURE);
}

NCarray nc_reshape(const NCarray arr, int new_shape_dim, ...){ 
    // Check for valid input array
    if(arr == NULL){
        fprintf(stderr, "Error in nc_reshape: The input array is NULL!\n");
        goto error;
    }
    //Init memory for the NCarray
    NCarray new_arr = nc_init_array();
    if(new_arr == NULL){
        fprintf(stderr, "Error in nc_reshape: Could not allocate new NCarray!\n");
        goto error;
    }strncpy(new_arr->type, arr->type, MAX_TYPE_LEN);
    // Check for valid new dimension
    if(new_shape_dim <= 0){
        fprintf(stderr, "Error in nc_reshape: new_shape_dim must be greater than 0!\n");
        goto error;
    }new_arr->ndim = new_shape_dim;

    // Check for valid new length
    va_list args;
    va_start(args, new_shape_dim);
    int new_length = 1;
    for(short int i = 0; i < new_shape_dim; i++){
        new_length *= va_arg(args, int);
    }
    if(new_length != arr->length){
        fprintf(stderr, "Error in nc_reshape: Cannot reshape array of shape (");
        for(int i = 0; i < arr->ndim; i++){
            fprintf(stderr, "%d", arr->shape[i]);
            if(i < arr->ndim - 1) fprintf(stderr, ", ");
        }
        fprintf(stderr, ") to shape (");
        va_start(args, new_shape_dim);
        for(short int i = 0; i < new_shape_dim; i++){
            fprintf(stderr, "%d", va_arg(args, int));
            if(i < new_shape_dim - 1) fprintf(stderr, ", ");
        }
        fprintf(stderr, ")!\n");
        goto error;
    }new_arr->length = new_length;

    // Set the new shape
    new_arr->shape = (int*) malloc(sizeof(int) * new_arr->ndim);
    va_start(args, new_shape_dim);
    for(int i = 0; i < new_arr->ndim; i++){
        new_arr->shape[i] = va_arg(args, int);
    }

    // Set the new data
    new_arr->data = arr->data;

    return new_arr;

    error:
        nc_collect();
        exit(EXIT_FAILURE);
}