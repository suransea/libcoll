//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_VECTOR_H
#define LIBCOLL_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_vector coll_vector_t;

coll_vector_t *coll_vector_new(size_t cap);

void *coll_vector_append(coll_vector_t *vector, void *data);

void *coll_vector_prepend(coll_vector_t *vector, void *data);

size_t coll_vector_size(coll_vector_t *vector);

void *coll_vector_at(coll_vector_t *vector, size_t index);

void *coll_vector_first(coll_vector_t *vector);

void *coll_vector_last(coll_vector_t *vector);

size_t coll_vector_index_of(coll_vector_t *vector, void *data);

size_t coll_vector_find(coll_vector_t *vector, bool (*pred)(void *));

void *coll_vector_insert_at(coll_vector_t *vector, void *data, size_t index);

void *coll_vector_insert_before(coll_vector_t *vector, void *data, void *pos);

void *coll_vector_insert_after(coll_vector_t *vector, void *data, void *pos);

void *coll_vector_assign(coll_vector_t *vector, size_t index, void *data);

void coll_vector_foreach(coll_vector_t *vector, void (*visit)(void *));

bool coll_vector_empty(coll_vector_t *vector);

void *coll_vector_remove(coll_vector_t *vector, void *data);

size_t coll_vector_remove_all(coll_vector_t *vector, void *data);

void *coll_vector_remove_if(coll_vector_t *vector, bool (*pred)(void *));

void *coll_vector_remove_at(coll_vector_t *vector, size_t index);

void *coll_vector_remove_first(coll_vector_t *vector);

void *coll_vector_remove_last(coll_vector_t *vector);

void coll_vector_clear(coll_vector_t *vector);

void coll_vector_free(coll_vector_t *vector);

#endif  //LIBCOLL_VECTOR_H
