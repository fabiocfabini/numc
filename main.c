#include <stdio.h>
#include <stdlib.h>

#include "includes/numc.h"



int main() {
    float fill_value = 3.23;
    NCarray arr1 = nc_zeros(NC_INT, 3, 2, 3, 4);
    NCarray arr2 = nc_ones(NC_INT, 3, 2, 3, 4);
    NCarray arr3 = nc_fill(NC_FLOAT, &fill_value, 3, 2, 3, 4);
    NCarray arr4 = nc_arange(NC_INT, 0, 10, 1);

    printf("arr1:\n");
    nc_show(arr1, 1, 0);
    printf("arr2:\n");
    nc_show(arr2, 1, 0);
    printf("arr3:\n");
    nc_show(arr3, 4, 2);
    printf("arr4:\n");
    nc_show(arr4, 1, 0);

    nc_save(arr1, "arr1.nc");
    nc_free_array(arr1);
    nc_free_array(arr2);

    NCarray arr5 = nc_load("arr1.nc");
    NCarray arr3_copy = nc_copy(arr3);
    NCarray arr4_reshaped = nc_reshape(arr4, 2, 2, 5);

    printf("arr3_copy:\n");
    nc_show(arr3_copy, 4, 2);
    printf("arr4_reshaped:\n");
    nc_show(arr4_reshaped, 1, 0);
    printf("arr5:\n");
    nc_show(arr5, 1, 0);

    // nc_collect();
    return 0;
}