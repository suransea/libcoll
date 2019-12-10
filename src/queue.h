//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_QUEUE_H
#define LIBCOLL_QUEUE_H

#include <stddef.h>
#include <stdbool.h>
#include "list.h"

typedef struct _queue Queue;

Queue *queue_new();

void queue_push(Queue *queue, void *data);

void *queue_pop(Queue *queue);

void *queue_front(Queue *queue);

void *queue_back(Queue *queue);

bool queue_empty(Queue *queue);

void queue_foreach(Queue *queue, void(*visit)(void *));

void queue_clear(Queue *queue);

size_t queue_size(Queue *queue);

void queue_free(Queue *queue);

#endif //LIBCOLL_QUEUE_H
