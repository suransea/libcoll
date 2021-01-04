//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_HSET_H
#define LIBCOLL_HSET_H

#include <stdbool.h>
#include <stddef.h>

#include "hmap.h"

typedef struct coll_hmap coll_hset_t;

coll_hset_t *coll_hset_new(size_t cap);

coll_hset_t *coll_hset_new_custom(size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *));

bool coll_hset_insert(coll_hset_t *set, void *data);

bool coll_hset_remove(coll_hset_t *set, void *data);

bool coll_hset_contains(coll_hset_t *set, void *data);

size_t coll_hset_size(coll_hset_t *set);

bool coll_hset_empty(coll_hset_t *set);

void coll_hset_foreach(coll_hset_t *set, void (*visit)(void *));

void coll_hset_clear(coll_hset_t *set);

void coll_hset_free(coll_hset_t *set);

#endif  //LIBCOLL_HSET_H
