//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_HMAP_H
#define LIBCOLL_HMAP_H

#include <stdbool.h>
#include <stddef.h>

#include "seq.h"

typedef struct coll_hmap HMap;

HMap *hmap_new(size_t cap);

HMap *hmap_new_custom(size_t cap, unsigned (*hash)(void *key), bool (*equal)(void *, void *));

void *hmap_insert(HMap *map, void *key, void *value);

void *hmap_value_of(HMap *map, void *key);

Seq *hmap_keys(HMap *map);

Seq *hmap_values(HMap *map);

size_t hmap_size(HMap *map);

bool hmap_empty(HMap *map);

bool hmap_contains_key(HMap *map, void *key);

bool hmap_contains_value(HMap *map, void *value);

void *hmap_remove(HMap *map, void *key);

void hmap_clear(HMap *map);

void hmap_foreach(HMap *map, void (*visit)(void *key, void *value));

void hmap_free(HMap *map);


// hash and equal functions

unsigned hash_ptr(void *);

unsigned hash_int(void *);

unsigned hash_char(void *);

unsigned hash_str(void *);

unsigned hash_double(void *);

bool equal_ptr(void *, void *);

bool equal_int(void *, void *);

bool equal_char(void *, void *);

bool equal_str(void *, void *);

bool equal_double(void *, void *);

#endif  // LIBCOLL_HMAP_H
