#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "../includes/numc.h"

int nc_sizeof(const char* type){
    if(strcmp(type, "i32") == 0){
        return sizeof(int);
    }else if(strcmp(type, "f32") == 0){
        return sizeof(float);
    }else{
        fprintf(stderr, "Error in nc_sizeof: type %s is not supported!\n", type);
        exit(EXIT_FAILURE);
    }
}

void nc_show_rec(NCarray arr, int depth, int* offset, int width, int precision){
    if(depth == arr->ndim-1){ // We reached the final dimension. It's time to print a column.
        putchar('[');
        if(strcmp(arr->type, "i32") == 0){
            int* data = ((int*) arr->data);
            for (int i = 0; i < arr->shape[depth]; i++){
                if(i == arr->shape[depth]-1){
                    printf("%*d", width, data[*offset + i]);
                    continue;
                }
                if(i == 0){
                    printf("%*d, ", width, data[*offset + i]);
                    continue;
                }
                printf("%*d, ", width, data[*offset + i]);
            }
        }else if(strcmp(arr->type, "f32") == 0){
            float* data = ((float*) arr->data);
            for (int i = 0; i < arr->shape[depth]; i++) {
                if(i == arr->shape[depth]-1){
                    printf(FFMT, width, precision, data[*offset + i]);
                    continue;
                }
                if(i == 0){
                    printf(FFMT", ", width, precision, data[*offset + i]);
                    continue;
                }
                printf(FFMT", ", width, precision, data[*offset + i]);
            }
        }else{
            fprintf(stderr, "Error in nc_show_rec: type %s is not supported!\n", arr->type);
            exit(EXIT_FAILURE);
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
            nc_show_rec(arr, depth+1, offset, width, precision);
        }
    }
    return; // We are done here. Return to the previous call.
}

void nc_show(NCarray arr, int width, int precision){
    int depth = 0;
    int offset = 0;
    printf("NCarray(");
    nc_show_rec(arr, depth, &offset, width, precision);
    printf(", type=%s)\n\n", arr->type);
}

void nc_save(NCarray arr, const char* filename){
    FILE* file = fopen(filename, "wb");
    if(file == NULL){
        fprintf(stderr, "Error in nc_save: could not open file %s!\n", filename);
        exit(EXIT_FAILURE);
    }
    fwrite(arr->type, sizeof(char), MAX_TYPE_LEN, file);
    fwrite(&arr->ndim, sizeof(int), 1, file);
    fwrite(arr->shape, sizeof(int), arr->ndim, file); // Length can be inferred from shape.
    fwrite(arr->data, nc_sizeof(arr->type), arr->length, file);
    fclose(file);
    return;
}

NCarray nc_load(const char* filename){
    FILE* file = fopen(filename, "rb");
    if(file == NULL){
        fprintf(stderr, "Error in nc_load: could not open file %s!\n", filename);
        goto error;
    }
    NCarray arr = nc_init_array();
    if(arr == NULL){
        fprintf(stderr, "Error in nc_load: could not allocate memory for NCarray!\n");
        goto error;
    }
    fread(arr->type, sizeof(char), MAX_TYPE_LEN, file);
    fread(&arr->ndim, sizeof(int), 1, file);
    arr->shape = malloc(sizeof(int) * arr->ndim);
    if(arr->shape == NULL){
        fprintf(stderr, "Error in nc_load: could not allocate memory for shape!\n");
        goto error;
    }
    fread(arr->shape, sizeof(int), arr->ndim, file);
    arr->length = 1;
    for(int i = 0; i < arr->ndim; i++)
        arr->length *= arr->shape[i];
    arr->data = malloc(nc_sizeof(arr->type) * arr->length);
    if(arr->data == NULL){
        fprintf(stderr, "Error in nc_load: could not allocate memory for data!\n");
        goto error;
    }
    fread(arr->data, nc_sizeof(arr->type), arr->length, file);
    fclose(file);

    GLOBAL->TOTAL_ARRAYS_CREATED++;
    arr->shared = 0;
    arr->data_idx = pop_from_nc_data();
    GLOBAL->DATA_TABLE[arr->data_idx].data = arr->data;
    GLOBAL->data_count++;
    return arr;

    error:
        // We need to free the memory we allocated before returning in case we failed to allocate memory for the array.
        if(arr->shape != NULL) free(arr->shape);

        exit(EXIT_FAILURE);
}