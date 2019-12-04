//
// Created by sea on 2019/11/28.
//

#include <stdlib.h>
#include "set.h"
#include "map.h"

struct _set {
  Map *map;
};

Set *set_new() {
    Set *set = malloc(sizeof(Set));
    set->map = map_new();
    return set;
}

Set *set_new_custom(int(*cmp)(void *, void *)) {
    Set *set = malloc(sizeof(Set));
    set->map = map_new_custom(cmp);
    return set;
}

bool set_add(Set *set, void *data) {
    if (set_contains(set, data)) {
        return false;
    }
    map_insert(set->map, data, data);
    return true;
}

void *set_remove(Set *set, void *data) {
    return map_remove(set->map, data);
}

bool set_contains(Set *set, void *data) {
    return map_contains_key(set->map, data);
}

size_t set_size(Set *set) {
    return map_size(set->map);
}

bool set_empty(Set *set) {
    return set_size(set) == 0;
}

void set_foreach(Set *set, void(*visit)(void *)) {
    Seq *seq = map_keys(set->map);
    seq_foreach(seq, visit);
    seq_free(seq);
}

void set_clear(Set *set) {
    map_clear(set->map);
}

void set_free(Set *set) {
    map_free(set->map);
    free(set);
}
