//
// Created by sea on 2019/11/28.
//

#include "coll/hset.h"

#define NON_NULL ((void *) 1)

void coll_hset_init(coll_hset_t *set, size_t cap) {
    coll_hmap_init(set, cap);
}

void coll_hset_new_custom(coll_hset_t *set, size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *)) {
    coll_hmap_init_custom(set, cap, hash, equal);
}

bool coll_hset_insert(coll_hset_t *set, void *data) {
    return NULL == coll_hmap_insert(set, data, NON_NULL);
}

bool coll_hset_remove(coll_hset_t *set, void *data) {
    return NON_NULL == coll_hmap_remove(set, data);
}

bool coll_hset_contains(coll_hset_t *set, void *data) {
    return coll_hmap_contains_key(set, data);
}

size_t coll_hset_size(coll_hset_t *set) {
    return coll_hmap_size(set);
}

bool coll_hset_empty(coll_hset_t *set) {
    return coll_hmap_empty(set);
}

void coll_hset_foreach(coll_hset_t *set, void (*visit)(void *)) {
    coll_seq_t seq = coll_hmap_keys(set);
    coll_seq_foreach(&seq, visit);
    coll_seq_free(&seq);
}

void coll_hset_clear(coll_hset_t *set) {
    coll_hmap_clear(set);
}

void coll_hset_free(coll_hset_t *set) {
    coll_hmap_free(set);
}
