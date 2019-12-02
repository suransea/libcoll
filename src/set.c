//
// Created by sea on 2019/11/28.
//

#include <stdlib.h>
#include "set.h"
#include "list.h"

struct _set {
  List *list;
};

Set *set_new() {
    Set *set = malloc(sizeof(Set));
    set->list = list_new();
    return set;
}

bool set_insert(Set *set, void *data) {
    if (set_contains(set, data)) {
        return false;
    }
    list_prepend(set->list, data);
    return true;
}

bool set_contains(Set *set, void *data) {
    int index = list_index_of(set->list, data);
    return index >= 0;
}