//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_HMAP_H
#define LIBCOLL_HMAP_H

#include <stdbool.h>
#include <stddef.h>

#include "seq.h"

typedef struct coll_hmap coll_hmap_t;

coll_hmap_t *coll_hmap_new(size_t cap);

coll_hmap_t *coll_hmap_new_custom(size_t cap, unsigned (*hash)(void *key), bool (*equal)(void *, void *));

void *coll_hmap_insert(coll_hmap_t *map, void *key, void *value);

void *coll_hmap_value_of(coll_hmap_t *map, void *key);

coll_seq_t *coll_hmap_keys(coll_hmap_t *map);

coll_seq_t *coll_hmap_values(coll_hmap_t *map);

size_t coll_hmap_size(coll_hmap_t *map);

bool coll_hmap_empty(coll_hmap_t *map);

bool coll_hmap_contains_key(coll_hmap_t *map, void *key);

bool coll_hmap_contains_value(coll_hmap_t *map, void *value);

void *coll_hmap_remove(coll_hmap_t *map, void *key);

void coll_hmap_clear(coll_hmap_t *map);

void coll_hmap_foreach(coll_hmap_t *map, void (*visit)(void *key, void *value));

void coll_hmap_free(coll_hmap_t *map);


// hash and equal functions

unsigned coll_hash_ptr(void *);

unsigned coll_hash_int(void *);

unsigned coll_hash_char(void *);

unsigned coll_hash_str(void *);

unsigned coll_hash_double(void *);

bool coll_equal_ptr(void *, void *);

bool coll_equal_int(void *, void *);

bool coll_equal_char(void *, void *);

bool coll_equal_str(void *, void *);

bool coll_equal_double(void *, void *);

#endif  //LIBCOLL_HMAP_H
