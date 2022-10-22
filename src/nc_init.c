#include <assert.h>
#include <stdlib.h>

#include "../includes/numc.h"

void add_to_nc_head(int index){
    Node new = (Node) malloc(sizeof(struct node));
    new->idx = index;
    new->next = GLOBAL_HEAD->nc_head;
    GLOBAL_HEAD->nc_head = new;
}

int pop_from_nc_head(){
    Node head = GLOBAL_HEAD->nc_head;
    int idx = head->idx;
    GLOBAL_HEAD->nc_head = head->next;
    free(head);
    return idx;
}

void add_to_nc_data(int index){
    Node new = (Node) malloc(sizeof(struct node));
    new->idx = index;
    new->next = GLOBAL_HEAD->nc_data;
    GLOBAL_HEAD->nc_data = new;
}

int pop_from_nc_data(){
    Node head = GLOBAL_HEAD->nc_data;
    int idx = head->idx;
    GLOBAL_HEAD->nc_data = head->next;
    free(head);
    return idx;
}

void nc_init_global_head(){
    GLOBAL_HEAD = (List) malloc(sizeof(struct list));
    GLOBAL_HEAD->nc_head = NULL;
    GLOBAL_HEAD->nc_data = NULL;

    for (int i = MAX_ARRAYS - 1; i > -1; i--){
        add_to_nc_head(i);
        add_to_nc_data(i);
    }
}

void nc_free_global_head(){
    if(GLOBAL_HEAD != NULL){
        Node head = GLOBAL_HEAD->nc_head;
        while (head != NULL){
            Node temp = head;
            head = head->next;
            free(temp);
        }
        Node data = GLOBAL_HEAD->nc_data;
        while (data != NULL){
            Node temp = data;
            data = data->next;
            free(temp);
        }
        free(GLOBAL_HEAD);
        GLOBAL_HEAD = NULL;
    }
}

void nc_free_array(NCarray arr){
    assert(arr != NULL && "NCarray to free is NULL");

    // Free the shape
    if(arr->shape != NULL){
        free(arr->shape);
    }
    //TODO: Freeing an unshared array should decrease the ref count of the data
    // Free the data if it not shared by another NCarray
    if(!arr->shared){
        int idx = arr->data_idx;
        free(arr->data);
        DATA_TABLE[idx] = NULL;
        data_count--;
        add_to_nc_data(idx);
    }
    int idx = arr->nc_idx;
    free(arr);
    NC_TABLE[idx] = NULL;
    nc_count--;
    add_to_nc_head(idx);
}

void nc_collect(){
    for(int i = 0; i <= TOTAL_ARRAYS_CREATED; i++){
        if(DATA_TABLE[i] != NULL){
            free(DATA_TABLE[i]);
            data_count--;
        }
    }TOTAL_ARRAYS_CREATED = -1;

    for (int i = 0; i <= TOTAL_NC_STRUCTS_CREATED; i++){
        if(NC_TABLE[i] != NULL){
            if(NC_TABLE[i]->shape != NULL){
                free(NC_TABLE[i]->shape);
            }
            free(NC_TABLE[i]);
            nc_count--;
        }
    }TOTAL_NC_STRUCTS_CREATED = -1;

    nc_free_global_head();
}

NCarray nc_init_array(){
    assert(nc_count < MAX_ARRAYS && "NCarray table is full");

    // If the global head is not initialized, initialize it
    if(!RUNNING){
        RUNNING = 1; atexit(nc_collect);
        nc_init_global_head();
    }

    // Set default values
    NCarray arr = malloc(sizeof(struct nc_array));
    if(arr == NULL) return NULL;
    arr->shared = -1;
    arr->length = 0;
    arr->data = NULL;
    arr->ndim = 0;
    arr->shape = NULL;
    arr->type[0] = '\0';

    // Add to the NC_TABLE in the first available index
    arr->nc_idx = pop_from_nc_head();
    (arr->nc_idx > TOTAL_NC_STRUCTS_CREATED)? TOTAL_NC_STRUCTS_CREATED = arr->nc_idx : 0;
    NC_TABLE[arr->nc_idx] = arr;
    nc_count++;
    return arr;
}