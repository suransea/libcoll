//
// Created by sea on 2019/11/28.
//

#include "coll/hset.h"

#define NON_NULL ((void *) 1)

HSet *hset_new(size_t cap) {
    return hmap_new(cap);
}

HSet *hset_new_custom(size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *)) {
    return hmap_new_custom(cap, hash, equal);
}

bool hset_insert(HSet *set, void *data) {
    return NULL == hmap_insert(set, data, NON_NULL);
}

bool hset_remove(HSet *set, void *data) {
    return NON_NULL == hmap_remove(set, data);
}

bool hset_contains(HSet *set, void *data) {
    return hmap_contains_key(set, data);
}

size_t hset_size(HSet *set) {
    return hmap_size(set);
}

bool hset_empty(HSet *set) {
    return hmap_empty(set);
}

void hset_foreach(HSet *set, void (*visit)(void *)) {
    Seq *seq = hmap_keys(set);
    seq_foreach(seq, visit);
    seq_free(seq);
}

void hset_clear(HSet *set) {
    hmap_clear(set);
}

void hset_free(HSet *set) {
    hmap_free(set);
}
