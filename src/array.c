//
// Created by sea on 2019/11/28.
//

#include "coll/array.h"

#include <stdlib.h>

void coll_array_init(coll_array_t *array, size_t len) {
    array->len = len;
    array->data = len == 0 ? NULL : calloc(len, sizeof(void *));
}

size_t coll_array_size(coll_array_t *array) {
    return array->len;
}

void *coll_array_at(coll_array_t *array, size_t index) {
    if (!array || index >= array->len) {
        return NULL;
    }
    return array->data[index];
}

void *coll_array_first(coll_array_t *array) {
    if (!array || array->len == 0) {
        return NULL;
    }
    return array->data[0];
}

void *coll_array_last(coll_array_t *array) {
    if (!array || array->len == 0) {
        return NULL;
    }
    return array->data[array->len - 1];
}

size_t coll_array_index_of(coll_array_t *array, void *data) {
    for (size_t i = 0; i < array->len; ++i) {
        if (array->data[i] == data) {
            return i;
        }
    }
    return array->len;
}

size_t coll_array_find(coll_array_t *array, bool (*pred)(void *)) {
    for (size_t i = 0; i < array->len; ++i) {
        if (pred(array->data[i])) {
            return i;
        }
    }
    return array->len;
}

void *coll_array_assign(coll_array_t *array, size_t index, void *data) {
    if (index >= array->len) {
        return NULL;
    }
    void *old = array->data[index];
    array->data[index] = data;
    return old;
}

void coll_array_foreach(coll_array_t *array, void (*visit)(void *)) {
    for (size_t i = 0; i < array->len; ++i) {
        visit(array->data[i]);
    }
}

bool coll_array_empty(coll_array_t *array) {
    return array->len == 0;
}

void coll_array_free(coll_array_t *array) {
    free(array->data);
}
