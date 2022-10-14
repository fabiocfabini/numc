#include <stdio.h>
#include <stdlib.h>

#include "../includes/numc.h"


int main() {
    NCarray arr = nc_zeros("i32", 2, 2, 2);

    // Add 1 to all the values
    for(int i = 0; i < arr->length; i++){
        ((int*)arr->data)[i] += 1;
    }

    // Print the values
    for(int i = 0; i < arr->length; i++){
        printf("%d ", ((int*)arr->data)[i]);
    }

    NCarray arr2 = nc_ones("f32", 2, 2, 2);

    // Add i to all the values
    for(int i = 0; i < arr2->length; i++){
        ((float*)arr2->data)[i] += 1;
    }printf("\n");

    // Print the values
    for(int i = 0; i < arr2->length; i++){
        printf("%.2f ", ((float*)arr2->data)[i]);
    }printf("\n");

    nc_free_array(arr);
    nc_free_array(arr2);
    return 0;
}