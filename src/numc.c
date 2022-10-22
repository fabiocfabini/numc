#include "../includes/numc.h"

int RUNNING = 0;
List GLOBAL_HEAD = {0};
int TOTAL_NC_STRUCTS_CREATED = -1;
int TOTAL_ARRAYS_CREATED = -1;
size_t nc_count = 0;
size_t data_count = 0;
NCarray NC_TABLE[MAX_ARRAYS] = {0};
void* DATA_TABLE[MAX_ARRAYS] = {0};