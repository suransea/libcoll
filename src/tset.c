//
// Created by sea on 2019/11/28.
//

#include "coll/tset.h"

#define NON_NULL ((void *) 1)

TSet *tset_new() {
    return tmap_new();
}

TSet *tset_new_custom(int (*cmp)(void *, void *)) {
    return tmap_new_custom(cmp);
}

bool tset_insert(TSet *set, void *data) {
    return NULL == tmap_insert(set, data, NON_NULL);
}

bool tset_remove(TSet *set, void *data) {
    return NON_NULL == tmap_remove(set, data);
}

bool tset_contains(TSet *set, void *data) {
    return tmap_contains_key(set, data);
}

size_t tset_size(TSet *set) {
    return tmap_size(set);
}

bool tset_empty(TSet *set) {
    return tmap_empty(set);
}

void tset_foreach(TSet *set, void (*visit)(void *)) {
    Seq *seq = tmap_keys(set);
    seq_foreach(seq, visit);
    seq_free(seq);
}

void tset_clear(TSet *set) {
    tmap_clear(set);
}

void tset_free(TSet *set) {
    tmap_free(set);
}
