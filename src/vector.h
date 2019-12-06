//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_VECTOR_H
#define LIBCOLL_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _vector Vector;

Vector *vector_new(size_t cap);

void *vector_append(Vector *vector, void *data);

void *vector_prepend(Vector *vector, void *data);

size_t vector_size(Vector *vector);

void *vector_at(Vector *vector, size_t index);

long vector_index_of(Vector *vector, void *data);

long vector_find(Vector *vector, bool (*pred)(void *));

void *vector_insert_at(Vector *vector, void *data, size_t index);

void *vector_insert_before(Vector *vector, void *data, void *pos);

void *vector_insert_after(Vector *vector, void *data, void *pos);

void *vector_assign(Vector *vector, size_t index, void *data);

void vector_foreach(Vector *vector, void(*visit)(void *));

bool vector_empty(Vector *vector);

void *vector_remove_last(Vector *vector);

void vector_clear(Vector *vector);

void vector_free(Vector *vector);

#endif //LIBCOLL_VECTOR_H
