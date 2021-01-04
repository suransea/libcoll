//
// Created by sea on 2019/12/4.
//

#include "coll/heap.h"

#include <stdlib.h>

#include "coll/vector.h"

struct coll_heap {
    coll_vector_t *vector;
    int (*cmp)(void *, void *);
};

static inline void swap(coll_heap_t *heap, size_t x, size_t y) {
    void *tmp = coll_vector_at(heap->vector, x);
    coll_vector_assign(heap->vector, x, coll_vector_at(heap->vector, y));
    coll_vector_assign(heap->vector, y, tmp);
}

static inline int cmp(coll_heap_t *heap, size_t x, size_t y) {
    return heap->cmp(coll_vector_at(heap->vector, x), coll_vector_at(heap->vector, y));
}

static void heapify_up(coll_heap_t *heap, size_t pos) {
    size_t parent = (pos - 1) / 2;
    while (pos > 0) {
        if (cmp(heap, pos, parent) < 0) {
            break;
        }
        swap(heap, pos, parent);
        pos = parent;
        parent = (pos - 1) / 2;
    }
}

static void heapify_down(coll_heap_t *heap, size_t pos) {
    size_t size = coll_vector_size(heap->vector);
    size_t l;
    while ((l = pos * 2 + 1) < size) {
        if (l < size - 1 && cmp(heap, l, l + 1) < 0) {
            ++l;  // right child
        }
        if (cmp(heap, pos, l) >= 0) {
            break;
        }
        swap(heap, pos, l);
        pos = l;
    }
}

coll_heap_t *coll_heap_new(int (*cmp)(void *, void *)) {
    coll_heap_t *heap = malloc(sizeof(coll_heap_t));
    heap->vector = coll_vector_new(8);
    heap->cmp = cmp;
    return heap;
}

void coll_heap_push(coll_heap_t *heap, void *data) {
    size_t pos = coll_vector_size(heap->vector);
    coll_vector_append(heap->vector, data);
    heapify_up(heap, pos);
}

void *coll_heap_pop(coll_heap_t *heap) {
    if (coll_vector_empty(heap->vector)) {
        return NULL;
    }
    size_t size = coll_vector_size(heap->vector);
    swap(heap, 0, size - 1);
    void *data = coll_vector_remove_last(heap->vector);
    heapify_down(heap, 0);
    return data;
}

void *coll_heap_top(coll_heap_t *heap) {
    if (coll_vector_empty(heap->vector)) {
        return NULL;
    }
    return coll_vector_at(heap->vector, 0);
}

size_t coll_heap_size(coll_heap_t *heap) {
    return coll_vector_size(heap->vector);
}

bool coll_heap_empty(coll_heap_t *heap) {
    return coll_vector_size(heap->vector) == 0;
}

void coll_heap_foreach(coll_heap_t *heap, void (*visit)(void *)) {
    coll_vector_foreach(heap->vector, visit);
}

void coll_heap_clear(coll_heap_t *heap) {
    coll_vector_clear(heap->vector);
}

void coll_heap_free(coll_heap_t *heap) {
    coll_vector_free(heap->vector);
    free(heap);
}
