//
// Created by sea on 2019/11/28.
//

#include <stdlib.h>
#include "queue.h"

struct _queue {
  List *list;
};

Queue *queue_new() {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = list_new();
    return queue;
}

void queue_push(Queue *queue, void *data) {
    list_append(queue->list, data);
}

void *queue_pop(Queue *queue) {
    if (list_size(queue->list) == 0) {
        return NULL;
    }
    void *data = list_first(queue->list);
    list_remove_first(queue->list);
    return data;
}

void *queue_front(Queue *queue) {
    return list_first(queue->list);
}

void *queue_back(Queue *queue) {
    return list_last(queue->list);
}

bool queue_empty(Queue *queue) {
    return list_size(queue->list) == 0;
}

size_t queue_size(Queue *queue) {
    return list_size(queue->list);
}

void queue_free(Queue *queue) {
    list_free(queue->list);
    free(queue);
}
