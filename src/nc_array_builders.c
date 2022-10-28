#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "../includes/numc.h"


NCarray nc_zeros(const char* type, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "[ERROR]: nc_zeros: Could not allocate memory for NCarray!\n");
        exit(EXIT_FAILURE);
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    va_list args;
    va_start(args, ndim);

    if(ndim <= 0){
        fprintf(stderr, "[ERROR]: nc_zeros: ndim must be greater than 0!\n");
        exit(EXIT_FAILURE);
    }
    arr->ndim = ndim;
    arr->length = 1;

    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    for(short int i = 0; i < arr->ndim; i++){
        arr->shape[i] = va_arg(args, int);
        arr->length *= arr->shape[i];
    }

    //Set all the values to 0
    if(strcmp(type, NC_INT) == 0){
        arr->data = (int*) calloc(arr->length, sizeof(int));
    }else if(strcmp(type, NC_FLOAT) == 0){
        arr->data = (float*) calloc(arr->length, sizeof(float));
    }else{
        fprintf(stderr, "[ERROR]: nc_zeros: type %s is not supported!\n", type);
        exit(EXIT_FAILURE);
    }

    arr->shared = 0;
    arr->data_idx = pop_from_nc_data();
    (arr->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = arr->data_idx : 0;
    (arr->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = arr->data_idx : 0;
    GLOBAL->DATA_TABLE[arr->data_idx].data = arr->data;
    GLOBAL->DATA_TABLE[arr->data_idx].ref_count = 1;
    GLOBAL->data_count++;

    return arr;
}

NCarray nc_ones(const char* type, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "[ERROR]: nc_ones: Could not allocate new NCarray!\n");
        exit(EXIT_FAILURE);
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    va_list args;
    va_start(args, ndim);

    if(ndim <= 0){
        fprintf(stderr, "[ERROR]: nc_ones: ndim must be greater than 0!\n");
        exit(EXIT_FAILURE);
    }
    arr->ndim = ndim;
    arr->length = 1;

    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    for(short int i = 0; i < arr->ndim; i++){
        arr->shape[i] = va_arg(args, int);
        arr->length *= arr->shape[i];
    }

    //Set all the values to 1
    if(strcmp(type, NC_INT) == 0){
        arr->data = (int*) calloc(arr->length, sizeof(int));
        for(int i = 0; i < arr->length; i++){
            ((int*) arr->data)[i] = 1;
        }
    }else if(strcmp(type, NC_FLOAT) == 0){
        arr->data = (float*) calloc(arr->length, sizeof(float));
        for(int i = 0; i < arr->length; i++){
            ((float*) arr->data)[i] = 1;
        }
    }else{
        fprintf(stderr, "[ERROR]: nc_ones: type %s is not supported!\n", type);
        exit(EXIT_FAILURE);
    }

    arr->shared = 0;
    arr->data_idx = pop_from_nc_data();
    (arr->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = arr->data_idx : 0;
    GLOBAL->DATA_TABLE[arr->data_idx].data = arr->data;
    GLOBAL->DATA_TABLE[arr->data_idx].ref_count = 1;
    GLOBAL->data_count++;

    return arr;
}

NCarray nc_arange(const char* type, int start, int stop, int step){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "[ERROR]: nc_arange: Could not allocate new NCarray!\n");
        exit(EXIT_FAILURE);
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    arr->ndim = 1;
    arr->length = (stop - start) / step;
    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    arr->shape[0] = arr->length;

    //Set all the values to 0
    if(strcmp(type, NC_INT) == 0){
        arr->data = (int*) malloc(sizeof(int) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((int*) arr->data)[i] = start + i * step;
        }
    }else if(strcmp(type, NC_FLOAT) == 0){
         arr->data = (float*) malloc(sizeof(float) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((float*) arr->data)[i] = (float)start + (float)i * (float)step;
        }
    }else{
        fprintf(stderr, "[ERROR]: nc_arange: type %s is not supported!\n", type);
        exit(EXIT_FAILURE);
    }

    arr->shared = 0;
    arr->data_idx = pop_from_nc_data();
    (arr->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = arr->data_idx : 0;
    GLOBAL->DATA_TABLE[arr->data_idx].data = arr->data;
    GLOBAL->DATA_TABLE[arr->data_idx].ref_count = 1;
    GLOBAL->data_count++;

    return arr;
}

NCarray nc_fill(const char* type, void* fill_value, int ndim, ...){
    //Init memory for the NCarray
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "[ERROR]: nc_fill: Could not allocate new NCarray!\n");
        exit(EXIT_FAILURE);
    }

    //Set the type of the struct
    strncpy(arr->type, type, MAX_TYPE_LEN);

    //Set the length and shape of the array
    va_list args;
    va_start(args, ndim);

    if(ndim <= 0){
        fprintf(stderr, "[ERROR]: nc_fill: ndim must be greater than 0!\n");
        exit(EXIT_FAILURE);
    }
    arr->ndim = ndim;
    arr->length = 1;

    arr->shape = (int*) malloc(sizeof(int) * arr->ndim);
    for(short int i = 0; i < arr->ndim; i++){
        arr->shape[i] = va_arg(args, int);
        arr->length *= arr->shape[i];
    }

    //Set all the values to 0
    if(strcmp(type, NC_INT) == 0){
        arr->data = (int*) malloc(sizeof(int) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((int*) arr->data)[i] = *((int*) fill_value);
        }
    }else if(strcmp(type, NC_FLOAT) == 0){
        arr->data = (float*) malloc(sizeof(float) * arr->length);
        for(int i = 0; i < arr->length; i++){
            ((float*) arr->data)[i] = *((float*) fill_value);
        }
    }else{
        fprintf(stderr, "[ERROR]: nc_fill: type %s is not supported!\n", type);
        exit(EXIT_FAILURE);
    }

    arr->shared = 0;
    arr->data_idx = pop_from_nc_data();
    (arr->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = arr->data_idx : 0;
    GLOBAL->DATA_TABLE[arr->data_idx].data = arr->data;
    GLOBAL->DATA_TABLE[arr->data_idx].ref_count = 1;
    GLOBAL->data_count++;

    return arr;
}

NCarray nc_reshape(const NCarray arr, int new_shape_dim, ...){ 
    // Check for valid input array
    if(arr == NULL){
        fprintf(stderr, "[ERROR]: nc_reshape: The input array is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //Init memory for the NCarray
    NCarray new_arr = nc_init_array();
    if(new_arr == NULL){
        fprintf(stderr, "[ERROR]: nc_reshape: Could not allocate new NCarray!\n");
        exit(EXIT_FAILURE);
    }strncpy(new_arr->type, arr->type, MAX_TYPE_LEN);
    // Check for valid new dimension
    if(new_shape_dim <= 0){
        fprintf(stderr, "[ERROR]: nc_reshape: new_shape_dim must be greater than 0!\n");
        exit(EXIT_FAILURE);
    }new_arr->ndim = new_shape_dim;

    // Check for valid new length
    va_list args;
    va_start(args, new_shape_dim);
    int new_length = 1;
    for(short int i = 0; i < new_shape_dim; i++){
        new_length *= va_arg(args, int);
    }
    if(new_length != arr->length){
        fprintf(stderr, "[ERROR]: nc_reshape: Cannot reshape array of shape (");
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
        exit(EXIT_FAILURE);
    }new_arr->length = new_length;

    // Set the new shape
    new_arr->shape = (int*) malloc(sizeof(int) * new_arr->ndim);
    va_start(args, new_shape_dim);
    for(int i = 0; i < new_arr->ndim; i++){
        new_arr->shape[i] = va_arg(args, int);
    }

    // Set the new data
    new_arr->data = arr->data;
    new_arr->data_idx = arr->data_idx;

    // Set the new shared flag
    new_arr->shared = arr->shared = 1;
    GLOBAL->DATA_TABLE[new_arr->data_idx].ref_count++;

    return new_arr;
}

NCarray nc_copy(NCarray src){
    // Check for valid input array
    if(src == NULL){
        fprintf(stderr, "[ERROR]: nc_copy: The input array is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //Init memory for the NCarray
    NCarray dst = nc_init_array();
    if(dst == NULL){
        fprintf(stderr, "[ERROR]: nc_copy: Could not allocate new NCarray!\n");
        exit(EXIT_FAILURE);
    }strncpy(dst->type, src->type, MAX_TYPE_LEN);

    // Set the new length and shape
    dst->ndim = src->ndim;
    dst->length = src->length;
    dst->shape = (int*) malloc(sizeof(int) * dst->ndim);
    for(int i = 0; i < dst->ndim; i++){
        dst->shape[i] = src->shape[i];
    }

    // Set the new data
    if(strcmp(dst->type, NC_INT) == 0){
        dst->data = (int*) malloc(sizeof(int) * dst->length);
        // use memcpy to copy the data
        memcpy(dst->data, src->data, sizeof(int) * dst->length);
    }else if(strcmp(dst->type, NC_FLOAT) == 0){
        dst->data = (float*) malloc(sizeof(float) * dst->length);
        // use memcpy to copy the data
        memcpy(dst->data, src->data, sizeof(float) * dst->length);
    }else{
        fprintf(stderr, "[ERROR]: nc_copy: type %s is not supported!\n", dst->type);
        exit(EXIT_FAILURE);
    }

    dst->shared = 0;
    dst->data_idx = pop_from_nc_data();
    (dst->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = dst->data_idx : 0;
    GLOBAL->DATA_TABLE[dst->data_idx].data = dst->data;
    GLOBAL->DATA_TABLE[dst->data_idx].ref_count = 1;
    GLOBAL->data_count++;

    return dst;
}

void nc_transpose_rec(NCarray src, NCarray dst, int* axis, int depth, int offset, int* index){
    int dim_offset = 1;
    for(int i = src->ndim-1; i > axis[depth]; i--){
        dim_offset *= src->shape[i];
    }
    if(depth == dst->ndim-2){ // We reached the final dimension. It's time to print a column.
        int last_dim_offset = 1;
        for(int i = src->ndim-1; i > axis[depth+1]; i--){
            last_dim_offset *= src->shape[i];
        }
        if(strcmp(dst->type, NC_INT) == 0){
            for(int i = 0; i < src->shape[axis[depth]]; i++){
                for(int j = 0; j < src->shape[axis[depth+1]]; j++){
                    ((int*)dst->data)[*index] = ((int*)src->data)[i * dim_offset + j * last_dim_offset + offset];
                    (*index)++;
                }
            }
        }else if (strcmp(dst->type, NC_FLOAT) == 0){
            for(int i = 0; i < src->shape[axis[depth]]; i++){
                for(int j = 0; j < src->shape[axis[depth+1]]; j++){
                    ((float*)dst->data)[*index] = ((float*)src->data)[i * dim_offset + j * last_dim_offset + offset];
                    (*index)++;
                }
            }
        }else{
            fprintf(stderr, "[ERROR]: nc_transpose_rec: type %s is not supported!\n", dst->type);
            exit(EXIT_FAILURE);
        }
    }else{
        for(int dim = 0; dim < src->shape[axis[depth]]; dim++){
            nc_transpose_rec(src, dst, axis, depth + 1, offset + dim * dim_offset, index);
        }
    }
}

NCarray nc_transpose(NCarray arr, int* axis, int size){
    // Check for valid input array
    if(arr == NULL){
        fprintf(stderr, "[ERROR]: nc_copy: The input array is NULL!\n");
        exit(EXIT_FAILURE);
    }

    //Init memory for the NCarray
    NCarray new = nc_init_array();
    if(new == NULL){
        fprintf(stderr, "[ERROR]: nc_copy: Could not allocate new NCarray!\n");
        exit(EXIT_FAILURE);
    }strncpy(new->type, arr->type, MAX_TYPE_LEN);

    // Check if axis is NULL
    int free_axis = 0;
    if(size != arr->ndim){
        fprintf(stderr, "[ERROR]: nc_transpose: The size of the axis array (%d) is not equal to the number of dimensions of the input array (%d)!\n", size, arr->ndim);
        exit(EXIT_FAILURE);
    }
    if(size == 1){ // arr is vector
        //TODO: MAKE the new array equal to the input array and share the data
        assert(0 && "Transposition of vector is not implemented yet!");
    }
    if(axis == NULL){
        free_axis = 1;
        axis = (int*) malloc(sizeof(int) * arr->ndim);
        for(int i = 0, j = arr->ndim-1; i < arr->ndim; i++, j--){
            axis[j] = i;
        }
    }

    // Set the new length and shape
    new->ndim = arr->ndim;
    new->length = arr->length;
    new->shape = (int*) malloc(sizeof(int) * new->ndim);
    for(int i = 0; i < arr->ndim; i++){
        new->shape[i] = arr->shape[axis[i]];
    }

    // Set the new data
    if(strcmp(new->type, NC_INT) == 0){
        new->data = (int*) malloc(sizeof(int) * new->length);
    }else if(strcmp(new->type, NC_FLOAT) == 0){
        new->data = (float*) malloc(sizeof(float) * new->length);
    }else{
        fprintf(stderr, "[ERROR]: nc_copy: type %s is not supported!\n", arr->type);
        exit(EXIT_FAILURE);
    }
    int index = 0;
    nc_transpose_rec(arr, new, axis, 0, 0, &index);

    new->shared = 0;
    new->data_idx = pop_from_nc_data();
    (new->data_idx > GLOBAL->TOTAL_ARRAYS_CREATED)? GLOBAL->TOTAL_ARRAYS_CREATED = new->data_idx : 0;
    GLOBAL->DATA_TABLE[new->data_idx].data = new->data;
    GLOBAL->DATA_TABLE[new->data_idx].ref_count = 1;
    GLOBAL->data_count++;

    // Free axis if it was malloced
    if(free_axis) free(axis);
    return new;
}