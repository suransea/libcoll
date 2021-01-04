//
// Created by sea on 2019/11/28.
//

#include "coll/queue.h"

#include "coll/deque.h"

coll_queue_t *coll_queue_new(size_t cap) {
    return coll_deque_new(cap);
}

void coll_queue_push(coll_queue_t *queue, void *data) {
    coll_deque_append(queue, data);
}

void *coll_queue_pop(coll_queue_t *queue) {
    return coll_deque_remove_first(queue);
}

void *coll_queue_front(coll_queue_t *queue) {
    return coll_deque_first(queue);
}

void *coll_queue_back(coll_queue_t *queue) {
    return coll_deque_last(queue);
}

bool coll_queue_empty(coll_queue_t *queue) {
    return coll_deque_empty(queue);
}

void coll_queue_foreach(coll_queue_t *queue, void (*visit)(void *)) {
    coll_deque_foreach(queue, visit);
}

void coll_queue_clear(coll_queue_t *queue) {
    coll_deque_clear(queue);
}

size_t coll_queue_size(coll_queue_t *queue) {
    return coll_deque_size(queue);
}

void coll_queue_free(coll_queue_t *queue) {
    coll_deque_free(queue);
}
