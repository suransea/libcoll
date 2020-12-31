//
// Created by sea on 2019/11/28.
//

#include "coll/queue.h"

#include "coll/deque.h"

Queue *queue_new(size_t cap) {
    return deque_new(cap);
}

void queue_push(Queue *queue, void *data) {
    deque_append(queue, data);
}

void *queue_pop(Queue *queue) {
    return deque_remove_first(queue);
}

void *queue_front(Queue *queue) {
    return deque_first(queue);
}

void *queue_back(Queue *queue) {
    return deque_last(queue);
}

bool queue_empty(Queue *queue) {
    return deque_empty(queue);
}

void queue_foreach(Queue *queue, void (*visit)(void *)) {
    deque_foreach(queue, visit);
}

void queue_clear(Queue *queue) {
    deque_clear(queue);
}

size_t queue_size(Queue *queue) {
    return deque_size(queue);
}

void queue_free(Queue *queue) {
    deque_free(queue);
}
