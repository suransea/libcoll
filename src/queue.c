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

void queue_enqueue(Queue *queue, void *data) {
    list_append(queue->list, data);
}

void *queue_dequeue(Queue *queue) {
    if (list_len(queue->list) == 0) {
        return NULL;
    }
    void *data = list_front(queue->list);
    list_remove_front(queue->list);
    return data;
}

void *queue_front(Queue *queue) {
    return list_front(queue->list);
}

void *queue_back(Queue *queue) {
    return list_back(queue->list);
}

bool queue_empty(Queue *queue) {
    return list_len(queue->list) == 0;
}
