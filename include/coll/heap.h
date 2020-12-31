//
// Created by sea on 2019/12/4.
//

#ifndef LIBCOLL_HEAP_H
#define LIBCOLL_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_heap Heap;

Heap *heap_new(int (*cmp)(void *, void *));

void heap_push(Heap *heap, void *data);

void *heap_pop(Heap *heap);

void *heap_top(Heap *heap);

size_t heap_size(Heap *heap);

bool heap_empty(Heap *heap);

void heap_foreach(Heap *heap, void (*visit)(void *));

void heap_clear(Heap *heap);

void heap_free(Heap *heap);

#endif  // LIBCOLL_HEAP_H
