//
// Created by sea on 2019/11/29.
//

#ifndef LIBCOLL_TMAP_H
#define LIBCOLL_TMAP_H

#include <stdbool.h>
#include <stddef.h>

#include "seq.h"

typedef struct coll_tmap coll_tmap_t;

coll_tmap_t *coll_tmap_new();

coll_tmap_t *coll_tmap_new_custom(int (*cmp)(void *, void *));

void *coll_tmap_insert(coll_tmap_t *map, void *key, void *value);

void *coll_tmap_value_of(coll_tmap_t *map, void *key);

coll_seq_t *coll_tmap_keys(coll_tmap_t *map);

coll_seq_t *coll_tmap_values(coll_tmap_t *map);

size_t coll_tmap_size(coll_tmap_t *map);

bool coll_tmap_empty(coll_tmap_t *map);

bool coll_tmap_contains_key(coll_tmap_t *map, void *key);

bool coll_tmap_contains_value(coll_tmap_t *map, void *value);

void *coll_tmap_remove(coll_tmap_t *map, void *key);

void coll_tmap_clear(coll_tmap_t *map);

void coll_tmap_foreach(coll_tmap_t *map, void (*visit)(void *key, void *value));

void coll_tmap_free(coll_tmap_t *map);


// compare functions

int coll_cmp_ptr(void *, void *);

int coll_cmp_int(void *, void *);

int coll_cmp_char(void *, void *);

int coll_cmp_str(void *, void *);

int coll_cmp_double(void *, void *);

#endif  // LIBCOLL_TMAP_H
