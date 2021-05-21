//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_TSET_H
#define LIBCOLL_TSET_H

#include <stdbool.h>
#include <stddef.h>

#include "coll/tmap.h"

typedef struct coll_tmap coll_tset_t;

void coll_tset_init(coll_tset_t *set);

void coll_tset_init_custom(coll_tset_t *set, int (*cmp)(void *, void *));

bool coll_tset_insert(coll_tset_t *set, void *data);

bool coll_tset_remove(coll_tset_t *set, void *data);

bool coll_tset_contains(coll_tset_t *set, void *data);

size_t coll_tset_size(coll_tset_t *set);

bool coll_tset_empty(coll_tset_t *set);

void coll_tset_foreach(coll_tset_t *set, void (*visit)(void *));

void coll_tset_clear(coll_tset_t *set);

void coll_tset_free(coll_tset_t *set);

#endif  //LIBCOLL_TSET_H
