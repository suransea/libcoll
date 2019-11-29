//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_QUEUE_H
#define LIBCOLL_QUEUE_H

#include <stdbool.h>
#include "list.h"

typedef struct _queue Queue;

Queue *queue_new();

void queue_enqueue(Queue *queue, void *data);

void *queue_dequeue(Queue *queue);

void *queue_front(Queue *queue);

void *queue_back(Queue *queue);

bool queue_empty(Queue *queue);

#endif //LIBCOLL_QUEUE_H
