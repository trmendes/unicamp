#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdint.h>
#include <stdlib.h>

#define ERR_HEAP_EMPTY -3
#define ERR_HEAP_FULL  -2
#define ERR_HEAP_NULL  -1
#define SUCCESS         EXIT_SUCCESS

#define LEFT(N)  ( (2 * N) + 1 )
#define RIGHT(N) ( (2 * N) + 2 )

typedef struct data_s {
    int32_t data;
} data_t;

typedef struct heap_ctrl_s {
    data_t      ** array;
    size_t         size;
    uint32_t       next;
} heap_ctrl_t;

heap_ctrl_t * hp_create        (size_t size);
int32_t       hp_insert_max    (heap_ctrl_t * heap, int32_t data);
int32_t       hp_insert_min    (heap_ctrl_t * heap, int32_t data);
int32_t       hp_remove_max    (heap_ctrl_t * heap);
int32_t       hp_remove_min    (heap_ctrl_t * heap);
int32_t       hp_heapfy_max    (heap_ctrl_t * heap);
int32_t       hp_heapfy_min    (heap_ctrl_t * heap);
int32_t       hp_get_head      (heap_ctrl_t * heap);
int32_t       hp_sort          (heap_ctrl_t * heap);
void          hp_print         (heap_ctrl_t * heap);
#endif