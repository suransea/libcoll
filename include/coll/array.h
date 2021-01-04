//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_ARRAY_H
#define LIBCOLL_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_array coll_array_t;

coll_array_t *coll_array_new(size_t len);

size_t coll_array_size(coll_array_t *array);

void *coll_array_at(coll_array_t *array, size_t index);

void *coll_array_first(coll_array_t *array);

void *coll_array_last(coll_array_t *array);

size_t coll_array_index_of(coll_array_t *array, void *data);

size_t coll_array_find(coll_array_t *array, bool (*pred)(void *));

void *coll_array_assign(coll_array_t *array, size_t index, void *data);

void coll_array_foreach(coll_array_t *array, void (*visit)(void *));

bool coll_array_empty(coll_array_t *array);

void coll_array_free(coll_array_t *array);

#endif  //LIBCOLL_ARRAY_H
