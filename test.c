#include <stdio.h>
#include "includes/numc.h"

int main(){
    nc_save(nc_zeros(NC_INT, 3, 2, 3, 4), "test/saved_arrays/zeros_i32_2x3x4.nc");
    nc_save(nc_zeros(NC_FLOAT, 3, 2, 3, 4), "test/saved_arrays/zeros_f32_2x3x4.nc");

    nc_save(nc_ones(NC_INT, 3, 2, 3, 4), "test/saved_arrays/ones_i32_2x3x4.nc");
    nc_save(nc_ones(NC_FLOAT, 3, 2, 3, 4), "test/saved_arrays/ones_f32_2x3x4.nc");

    nc_save(nc_arange(NC_INT, -10, 10, 2), "test/saved_arrays/arange_i32_range(-10,10).nc");
    nc_save(nc_arange(NC_FLOAT, -10, 10, 2), "test/saved_arrays/arange_f32_range(-10,10).nc");

    int ival = 12;
    float fval = 12.0;
    nc_save(nc_fill(NC_INT, &ival, 3, 2, 3, 4), "test/saved_arrays/fill_i32_12.nc");
    nc_save(nc_fill(NC_FLOAT, &fval, 3, 2, 3, 4), "test/saved_arrays/fill_f32_12.nc");

    printf("Hello, World!\n");

    return 0;
}

//NOTE: Testing system could probably be improved by using a testing framework or by using Python to run the tests
// int main(){
//     int total = 0;
//     int passed = 0;
//     int failed = 0;

//     if(total == 0){
//         printf("No tests to run.\n");
//         return 0;
//     }else{
//         printf("[INFO] STARTED TESTS\n");

//         printf("[INFO] REPORT: %d/ %d tests passed (%f%%). Failed %d.\n", passed, total, passed/total * 100.0, failed);
//     }

//     return 0;
// }

