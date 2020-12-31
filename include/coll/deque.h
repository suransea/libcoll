//
// Created by sea on 2019/11/29.
//

#ifndef LIBCOLL_DEQUE_H
#define LIBCOLL_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_deque Deque;

Deque *deque_new(size_t cap);

void *deque_append(Deque *deque, void *data);

void *deque_prepend(Deque *deque, void *data);

size_t deque_size(Deque *deque);

void *deque_first(Deque *deque);

void *deque_last(Deque *deque);

void *deque_at(Deque *deque, size_t index);

size_t deque_index_of(Deque *deque, void *data);

size_t deque_find(Deque *deque, bool (*pred)(void *));

void *deque_assign(Deque *deque, size_t index, void *data);

void *deque_insert_at(Deque *deque, void *data, size_t index);

void *deque_insert_before(Deque *deque, void *data, void *pos);

void *deque_insert_after(Deque *deque, void *data, void *pos);

void *deque_remove(Deque *deque, void *data);

size_t deque_remove_all(Deque *deque, void *data);

void *deque_remove_if(Deque *deque, bool (*pred)(void *));

void *deque_remove_at(Deque *deque, size_t index);

void *deque_remove_first(Deque *deque);

void *deque_remove_last(Deque *deque);

void deque_foreach(Deque *deque, void (*visit)(void *));

bool deque_empty(Deque *deque);

void deque_clear(Deque *deque);

void deque_free(Deque *deque);

#endif  // LIBCOLL_DEQUE_H
