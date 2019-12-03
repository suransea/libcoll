//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_RING_H
#define LIBCOLL_RING_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _ring Ring;

struct _ring {
  void *data;
  Ring *next, *prev;
};

Ring *ring_new(size_t len);

Ring *ring_insert(Ring *ring, void *data);

Ring *ring_remove(Ring *ring, void *data);

Ring *ring_remove_all(Ring *ring, void *data);

Ring *ring_remove_if(Ring *ring, bool (*pred)(void *));

size_t ring_len(Ring *ring);

Ring *ring_move(Ring *ring, int n);

void ring_foreach(Ring *ring, void(*visit)(void *));

void ring_free(Ring *ring);

#endif //LIBCOLL_RING_H
