//
// Created by sea on 2019/12/4.
//

#ifndef LIBCOLL_HEAP_H
#define LIBCOLL_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_heap coll_heap_t;

coll_heap_t *coll_heap_new(int (*cmp)(void *, void *));

void coll_heap_push(coll_heap_t *heap, void *data);

void *coll_heap_pop(coll_heap_t *heap);

void *coll_heap_top(coll_heap_t *heap);

size_t coll_heap_size(coll_heap_t *heap);

bool coll_heap_empty(coll_heap_t *heap);

void coll_heap_foreach(coll_heap_t *heap, void (*visit)(void *));

void coll_heap_clear(coll_heap_t *heap);

void coll_heap_free(coll_heap_t *heap);

#endif  //LIBCOLL_HEAP_H
