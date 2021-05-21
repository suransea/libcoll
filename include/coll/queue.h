//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_QUEUE_H
#define LIBCOLL_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "coll/deque.h"

typedef struct coll_deque coll_queue_t;

void coll_queue_init(coll_queue_t *queue, size_t cap);

void coll_queue_push(coll_queue_t *queue, void *data);

void *coll_queue_pop(coll_queue_t *queue);

void *coll_queue_front(coll_queue_t *queue);

void *coll_queue_back(coll_queue_t *queue);

bool coll_queue_empty(coll_queue_t *queue);

void coll_queue_foreach(coll_queue_t *queue, void (*visit)(void *));

void coll_queue_clear(coll_queue_t *queue);

size_t coll_queue_size(coll_queue_t *queue);

void coll_queue_free(coll_queue_t *queue);

#endif  //LIBCOLL_QUEUE_H
