//
// Created by sea on 2019/11/29.
//

#ifndef LIBCOLL_TMAP_H
#define LIBCOLL_TMAP_H

#include <stdbool.h>
#include <stddef.h>

#include "seq.h"

typedef struct coll_tmap TMap;

TMap *tmap_new();

TMap *tmap_new_custom(int (*cmp)(void *, void *));

void *tmap_insert(TMap *map, void *key, void *value);

void *tmap_value_of(TMap *map, void *key);

Seq *tmap_keys(TMap *map);

Seq *tmap_values(TMap *map);

size_t tmap_size(TMap *map);

bool tmap_empty(TMap *map);

bool tmap_contains_key(TMap *map, void *key);

bool tmap_contains_value(TMap *map, void *value);

void *tmap_remove(TMap *map, void *key);

void tmap_clear(TMap *map);

void tmap_foreach(TMap *map, void (*visit)(void *key, void *value));

void tmap_free(TMap *map);


// compare functions

int cmp_ptr(void *, void *);

int cmp_int(void *, void *);

int cmp_char(void *, void *);

int cmp_str(void *, void *);

int cmp_double(void *, void *);

#endif  // LIBCOLL_TMAP_H
