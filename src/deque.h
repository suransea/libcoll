//
// Created by sea on 2019/11/29.
//

#ifndef LIBCOLL_DEQUE_H
#define LIBCOLL_DEQUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _deque Deque;

Deque *deque_new();

void deque_append(Deque *deque, void *data);

void deque_prepend(Deque *deque, void *data);

size_t deque_size(Deque *deque);

void *deque_at(Deque *deque, size_t index);

void *deque_assign(Deque *deque, size_t index, void *data);

void *deque_remove_front(Deque *deque);

void *deque_remove_back(Deque *deque);

void deque_foreach(Deque *deque, void(*visit)(void *));

bool deque_empty(Deque *deque);

void deque_clear(Deque *deque);

void deque_free(Deque *deque);

#endif //LIBCOLL_DEQUE_H
