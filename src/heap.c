//
// Created by sea on 2019/12/4.
//

#include <stdlib.h>
#include "heap.h"
#include "vector.h"

struct _heap {
  Vector *vector;
  int (*cmp)(void *, void *);
};

static inline void _swap(Heap *heap, size_t x, size_t y) {
    void *tmp = vector_at(heap->vector, x);
    vector_assign(heap->vector, x, vector_at(heap->vector, y));
    vector_assign(heap->vector, y, tmp);
}

static inline int _cmp(Heap *heap, size_t x, size_t y) {
    return heap->cmp(vector_at(heap->vector, x), vector_at(heap->vector, y));
}

static void _heapify_up(Heap *heap, size_t pos) {
    size_t parent = (pos - 1) / 2;
    while (pos > 0) {
        if (_cmp(heap, pos, parent) < 0) {
            break;
        }
        _swap(heap, pos, parent);
        pos = parent;
        parent = (pos - 1) / 2;
    }
}

static void _heapify_down(Heap *heap, size_t pos) {
    size_t size = vector_size(heap->vector);
    size_t l = pos * 2 + 1;
    while (l < size) {
        if (l < size - 1 && _cmp(heap, l, l + 1) < 0) {
            ++l; // right child
        }
        if (_cmp(heap, pos, l) >= 0) {
            break;
        }
        _swap(heap, pos, l);
        pos = l;
        l = pos * 2 + 1;
    }
}

Heap *heap_new(int (*cmp)(void *, void *)) {
    Heap *heap = malloc(sizeof(Heap));
    heap->vector = vector_new(8);
    heap->cmp = cmp;
    return heap;
}

void heap_push(Heap *heap, void *data) {
    size_t pos = vector_size(heap->vector);
    vector_append(heap->vector, data);
    _heapify_up(heap, pos);
}

void *heap_pop(Heap *heap) {
    if (vector_empty(heap->vector)) {
        return NULL;
    }
    size_t size = vector_size(heap->vector);
    _swap(heap, 0, size - 1);
    void *data = vector_remove_last(heap->vector);
    _heapify_down(heap, 0);
    return data;
}

void *heap_top(Heap *heap) {
    if (vector_empty(heap->vector)) {
        return NULL;
    }
    return vector_at(heap->vector, 0);
}

size_t heap_size(Heap *heap) {
    return vector_size(heap->vector);
}

bool heap_empty(Heap *heap) {
    return vector_size(heap->vector) == 0;
}

void heap_clear(Heap *heap) {
    vector_clear(heap->vector);
}

void heap_free(Heap *heap) {
    vector_free(heap->vector);
    free(heap);
}
