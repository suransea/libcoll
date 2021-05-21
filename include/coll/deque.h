//
// Created by sea on 2019/11/29.
//

#ifndef LIBCOLL_DEQUE_H
#define LIBCOLL_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

struct coll_deque {
    void **data;
    size_t len, cap, head, tail;
};

typedef struct coll_deque coll_deque_t;

void coll_deque_init(coll_deque_t *deque, size_t cap);

void *coll_deque_append(coll_deque_t *deque, void *data);

void *coll_deque_prepend(coll_deque_t *deque, void *data);

size_t coll_deque_size(coll_deque_t *deque);

void *coll_deque_first(coll_deque_t *deque);

void *coll_deque_last(coll_deque_t *deque);

void *coll_deque_at(coll_deque_t *deque, size_t index);

size_t coll_deque_index_of(coll_deque_t *deque, void *data);

size_t coll_deque_find(coll_deque_t *deque, bool (*pred)(void *));

void *coll_deque_assign(coll_deque_t *deque, size_t index, void *data);

void *coll_deque_insert_at(coll_deque_t *deque, void *data, size_t index);

void *coll_deque_insert_before(coll_deque_t *deque, void *data, void *pos);

void *coll_deque_insert_after(coll_deque_t *deque, void *data, void *pos);

void *coll_deque_remove(coll_deque_t *deque, void *data);

size_t coll_deque_remove_all(coll_deque_t *deque, void *data);

void *coll_deque_remove_if(coll_deque_t *deque, bool (*pred)(void *));

void *coll_deque_remove_at(coll_deque_t *deque, size_t index);

void *coll_deque_remove_first(coll_deque_t *deque);

void *coll_deque_remove_last(coll_deque_t *deque);

void coll_deque_foreach(coll_deque_t *deque, void (*visit)(void *));

bool coll_deque_empty(coll_deque_t *deque);

void coll_deque_clear(coll_deque_t *deque);

void coll_deque_free(coll_deque_t *deque);

#endif  //LIBCOLL_DEQUE_H
