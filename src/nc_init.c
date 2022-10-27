#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../includes/numc.h"

void add_to_nc_head(int index){
    Node new = (Node) malloc(sizeof(struct node));
    new->idx = index;
    new->next = GLOBAL->HEAD->nc_head;
    GLOBAL->HEAD->nc_head = new;
}

int pop_from_nc_head(){
    Node head = GLOBAL->HEAD->nc_head;
    int idx = head->idx;
    GLOBAL->HEAD->nc_head = head->next;
    free(head);
    return idx;
}

void add_to_nc_data(int index){
    Node new = (Node) malloc(sizeof(struct node));
    new->idx = index;
    new->next = GLOBAL->HEAD->nc_data;
    GLOBAL->HEAD->nc_data = new;
}

int pop_from_nc_data(){
    Node head = GLOBAL->HEAD->nc_data;
    int idx = head->idx;
    GLOBAL->HEAD->nc_data = head->next;
    free(head);
    return idx;
}

void nc_init_global_head(){
    GLOBAL->HEAD = (List) malloc(sizeof(struct list));
    GLOBAL->HEAD->nc_head = NULL;
    GLOBAL->HEAD->nc_data = NULL;

    for (int i = MAX_ARRAYS - 1; i > -1; i--){
        add_to_nc_head(i);
        add_to_nc_data(i);
    }
}

void nc_free_global_head(){
    if(GLOBAL->HEAD != NULL){
        Node head = GLOBAL->HEAD->nc_head;
        while (head != NULL){
            Node temp = head;
            head = head->next;
            free(temp);
        }
        Node data = GLOBAL->HEAD->nc_data;
        while (data != NULL){
            Node temp = data;
            data = data->next;
            free(temp);
        }
        free(GLOBAL->HEAD);
        GLOBAL->HEAD = NULL;
    }
}

void nc_free_globals(){
    nc_free_global_head();
    free(GLOBAL);
}

void nc_init_globals(){
    GLOBAL = (GLOBALS) malloc(sizeof(struct globals));

    if (GLOBAL == NULL){
        fprintf(stderr, "Error: Could not allocate memory for GLOBALS struct");
        exit(1);
    }

    for (int i = 0; i < MAX_ARRAYS; i++){
        GLOBAL->NC_TABLE[i] = NULL;
        GLOBAL->DATA_TABLE[i] = NULL;
    }
    GLOBAL->nc_count = GLOBAL->data_count = 0;
    GLOBAL->TOTAL_NC_STRUCTS_CREATED = -1;
    GLOBAL->TOTAL_ARRAYS_CREATED = -1;

    nc_init_global_head();
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
        GLOBAL->DATA_TABLE[idx] = NULL;
        GLOBAL->data_count--;
        add_to_nc_data(idx);
    }
    int idx = arr->nc_idx;
    free(arr);
    GLOBAL->NC_TABLE[idx] = NULL;
    GLOBAL->nc_count--;
    add_to_nc_head(idx);
}

void nc_collect(){
    for(int i = 0; i <= GLOBAL->TOTAL_ARRAYS_CREATED; i++){
        if(GLOBAL->DATA_TABLE[i] != NULL){
            free(GLOBAL->DATA_TABLE[i]);
            GLOBAL->data_count--;
        }
    }GLOBAL->TOTAL_ARRAYS_CREATED = -1;

    for (int i = 0; i <= GLOBAL->TOTAL_NC_STRUCTS_CREATED; i++){
        if(GLOBAL->NC_TABLE[i] != NULL){
            if(GLOBAL->NC_TABLE[i]->shape != NULL){
                free(GLOBAL->NC_TABLE[i]->shape);
            }
            free(GLOBAL->NC_TABLE[i]);
            GLOBAL->nc_count--;
        }
    }GLOBAL->TOTAL_NC_STRUCTS_CREATED = -1;

    nc_free_globals();
}

NCarray nc_init_array(){
    if(GLOBAL)
        assert(GLOBAL->nc_count < MAX_ARRAYS && "NCarray table is full");

    // If the global head is not initialized, initialize it
    if(!RUNNING){
        RUNNING = 1; atexit(nc_collect);
        nc_init_globals(); //TODO: Implement this and support for GLOBALS struct
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

    // Add to the GLOBAL->NC_TABLE in the first available index
    arr->nc_idx = pop_from_nc_head();
    (arr->nc_idx > GLOBAL->TOTAL_NC_STRUCTS_CREATED)? GLOBAL->TOTAL_NC_STRUCTS_CREATED = arr->nc_idx : 0;
    GLOBAL->NC_TABLE[arr->nc_idx] = arr;
    GLOBAL->nc_count++;
    return arr;
}