//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_VECTOR_H
#define LIBCOLL_VECTOR_H

#include <stddef.h>

typedef struct _vector Vector;

struct _vector {
  void **data;
  size_t len;
  size_t cap;
};

Vector *vector_new(size_t cap);

void vector_append(Vector *vector, void *data);

void *vector_at(Vector *vector, int index);

void vector_set(Vector *vector, int index, void *data);

void vector_foreach(Vector *vector, void(*visit)(void *));

#endif //LIBCOLL_VECTOR_H
