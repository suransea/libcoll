//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_HSET_H
#define LIBCOLL_HSET_H

#include <stdbool.h>
#include <stddef.h>

#include "hmap.h"

typedef struct coll_hmap HSet;

HSet *hset_new(size_t cap);

HSet *hset_new_custom(size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *));

bool hset_insert(HSet *set, void *data);

bool hset_remove(HSet *set, void *data);

bool hset_contains(HSet *set, void *data);

size_t hset_size(HSet *set);

bool hset_empty(HSet *set);

void hset_foreach(HSet *set, void (*visit)(void *));

void hset_clear(HSet *set);

void hset_free(HSet *set);

#endif  //LIBCOLL_HSET_H
