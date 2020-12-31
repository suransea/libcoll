//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_ARRAY_H
#define LIBCOLL_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_array Array;

Array *array_new(size_t len);

size_t array_size(Array *array);

void *array_at(Array *array, size_t index);

void *array_first(Array *array);

void *array_last(Array *array);

size_t array_index_of(Array *array, void *data);

size_t array_find(Array *array, bool (*pred)(void *));

void *array_assign(Array *array, size_t index, void *data);

void array_foreach(Array *array, void (*visit)(void *));

bool array_empty(Array *array);

void array_free(Array *array);

#endif  //LIBCOLL_ARRAY_H
