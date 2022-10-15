#include <stdio.h>
#include <stdlib.h>

#include "../includes/numc.h"

int main() {
    NCarray arr1 = nc_zeros("i32", 2, 2, 2);
    NCarray arr2 = nc_zeros("i32", 2, 2, 2);

    nc_equal(arr1, arr2);

    nc_collect();
    return 0;
}