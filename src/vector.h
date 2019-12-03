//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_VECTOR_H
#define LIBCOLL_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _vector Vector;

Vector *vector_new(size_t cap);

void vector_append(Vector *vector, void *data);

size_t vector_len(Vector *vector);

void *vector_at(Vector *vector, int index);

void *vector_assign(Vector *vector, int index, void *data);

void vector_foreach(Vector *vector, void(*visit)(void *));

bool vector_empty(Vector *vector);

void vector_clear(Vector *vector);

void vector_free(Vector *vector);

#endif //LIBCOLL_VECTOR_H
