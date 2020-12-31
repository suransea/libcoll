//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_TSET_H
#define LIBCOLL_TSET_H

#include <stdbool.h>
#include <stddef.h>

#include "tmap.h"

typedef struct coll_tmap TSet;

TSet *tset_new();

TSet *tset_new_custom(int (*cmp)(void *, void *));

bool tset_insert(TSet *set, void *data);

bool tset_remove(TSet *set, void *data);

bool tset_contains(TSet *set, void *data);

size_t tset_size(TSet *set);

bool tset_empty(TSet *set);

void tset_foreach(TSet *set, void (*visit)(void *));

void tset_clear(TSet *set);

void tset_free(TSet *set);

#endif  //LIBCOLL_TSET_H
