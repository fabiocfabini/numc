#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "../includes/numc.h"

void nc_free_array(NCarray arr){
    assert(arr != NULL && "NCarray to free is NULL");
    if(arr->data != NULL) free(arr->data);
    if(arr->shape != NULL) free(arr->shape);
    free(arr);
    nc_count--;
}

void nc_collect(){
    int total = nc_count;
    for (size_t i = 0; i < total && NC_TABLE[i] != 0; i++)
        nc_free_array(NC_TABLE[i]);
}

NCarray nc_init_array(){
    assert(nc_count < NC_TABLE_CAP && "NCarray table is full");

    NCarray arr = malloc(sizeof(struct nc_array));
    if(arr == NULL) return NULL;
    arr->length = 0;
    arr->data = NULL;
    arr->ndim = 0;
    arr->shape = NULL;
    arr->type[0] = '\0';

    NC_TABLE[nc_count++] = arr;
    return arr;
}

int nc_equal(NCarray arr1, NCarray arr2){
    int equal = 1;

    // Check for valid arrays
    if(arr1 == NULL || arr2 == NULL){
        fprintf(stderr, "Error in nc_equal: One of the arrays is NULL! &arr1 = %p, &arr2 = %p\n", arr1, arr2);
        goto error;
    }

    // Check for equal length
    if(arr1->length != arr2->length){
        fprintf(stderr, "Could not compare arrays due to unequal length (%d != %d)", arr1->length, arr2->length);
        goto error;
    }

    // Check for equal type
    if(strcmp(arr1->type, arr2->type) != 0){
        fprintf(stderr, "Could not compare arrays due to unequal type (%s != %s)", arr1->type, arr2->type);
        goto error;
    }

    // Check for equal shapes
    if(arr1->ndim != arr2->ndim || memcmp(arr1->shape, arr2->shape, arr1->ndim * sizeof(short int)) != 0){
        fprintf(stderr, "Could not compare arrays due to unequal dimensions (%d != %d)", arr1->ndim, arr2->ndim);
        goto error;
    }

    // Check for equal data
    if(strcmp(arr1->type, "i32") == 0){
        if(memcmp(arr1->data, arr2->data, arr1->length * sizeof(float)) != 0) equal = 0;
    }else if(strcmp(arr1->type, "f32") == 0){
        if(memcmp(arr1->data, arr2->data, arr1->length * sizeof(float)) != 0) equal = 0;
    }else{
        fprintf(stderr, "Error in nc_cmp: type %s is not supported!\n", arr1->type);
        goto error;
    }
    return equal;

    error:
        nc_collect();
        exit(EXIT_FAILURE);
}

void nc_show_rec(NCarray arr, int depth, int* offset){
    if(depth == arr->ndim-1){ // We reached the final dimension. It's time to print a column.
        putchar('[');
        if(strcmp(arr->type, "i32") == 0){
            int* data = ((int*)arr->data);
            for (int i = 0; i < arr->shape[depth]; i++){
                if(i == arr->shape[depth]-1){
                    printf("%d", data[*offset + i]);
                    continue;
                }
                if(i == 0){
                    printf("%d, ", data[*offset + i]);
                    continue;
                }
                printf("%d, ", data[*offset + i]);
            }
        }else if(strcmp(arr->type, "f32") == 0){
            float* data = ((float*)arr->data);
            for (int i = 0; i < arr->shape[depth]; i++)
                printf("%-5f ", data[*offset + i]);
        }else{
            fprintf(stderr, "Error in nc_show_rec: type %s is not supported!\n", arr->type);
            goto error;
        }
        *offset += (int) arr->shape[depth];
        for(int i = 0; i < arr->ndim; i++){
            int inner_length = 1;
            for(int j = i; j < arr->ndim; j++)
                inner_length *= arr->shape[j];
            if((*offset) % inner_length == 0){
                for(int j = 0; j < arr->ndim-i; j++)
                    putchar(']');
                if(i != 0){
                    (i != arr->ndim-1)? printf(",\n\n"): printf(",\n");
                    for(int j = 0; j < 8; j++)
                        putchar(' ');
                    int chars_to_add = arr->ndim -  1;
                    for(int j = 0; j < i; j++){
                        putchar(' '); chars_to_add--;
                    }
                    for(; chars_to_add > 0; chars_to_add--)
                        putchar('[');
                }
                break;
            }
        }
    }else{ // We are not in the final dimension. We need to call the function again.
        for(int i = 0; i < arr->shape[depth]; i++){
            if (*offset == 0) putchar('[');
            nc_show_rec(arr, depth+1, offset);
        }
    }
    return; // We are done here. Return to the previous call.

    error:
        nc_collect();
        exit(EXIT_FAILURE);
}

void nc_show(NCarray arr){
    int depth = 0;
    int offset = 0;
    printf("\nNCarray(");
    nc_show_rec(arr, depth, &offset);
    printf(", type=%s)\n", arr->type);
}