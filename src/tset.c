//
// Created by sea on 2019/11/28.
//

#include "coll/tset.h"

#define NON_NULL ((void *) 1)

void coll_tset_init(coll_tset_t *set) {
    coll_tmap_init(set);
}

void coll_tset_new_custom(coll_tset_t *set, int (*cmp)(void *, void *)) {
    coll_tmap_init_custom(set, cmp);
}

bool coll_tset_insert(coll_tset_t *set, void *data) {
    return NULL == coll_tmap_insert(set, data, NON_NULL);
}

bool coll_tset_remove(coll_tset_t *set, void *data) {
    return NON_NULL == coll_tmap_remove(set, data);
}

bool coll_tset_contains(coll_tset_t *set, void *data) {
    return coll_tmap_contains_key(set, data);
}

size_t coll_tset_size(coll_tset_t *set) {
    return coll_tmap_size(set);
}

bool coll_tset_empty(coll_tset_t *set) {
    return coll_tmap_empty(set);
}

void coll_tset_foreach(coll_tset_t *set, void (*visit)(void *)) {
    coll_seq_t seq = coll_tmap_keys(set);
    coll_seq_foreach(&seq, visit);
    coll_seq_free(&seq);
}

void coll_tset_clear(coll_tset_t *set) {
    coll_tmap_clear(set);
}

void coll_tset_free(coll_tset_t *set) {
    coll_tmap_free(set);
}
