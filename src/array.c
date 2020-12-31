//
// Created by sea on 2019/11/28.
//

#include "coll/array.h"

#include <stdlib.h>

struct coll_array {
    void **data;
    size_t len;
};

Array *array_new(size_t len) {
    Array *array = malloc(sizeof(Array));
    array->len = len;
    array->data = len == 0 ? NULL : calloc(len, sizeof(void *));
    return array;
}

size_t array_size(Array *array) {
    return array->len;
}

void *array_at(Array *array, size_t index) {
    if (!array || index >= array->len) {
        return NULL;
    }
    return array->data[index];
}

void *array_first(Array *array) {
    if (!array || array->len == 0) {
        return NULL;
    }
    return array->data[0];
}

void *array_last(Array *array) {
    if (!array || array->len == 0) {
        return NULL;
    }
    return array->data[array->len - 1];
}

size_t array_index_of(Array *array, void *data) {
    for (size_t i = 0; i < array->len; ++i) {
        if (array->data[i] == data) {
            return i;
        }
    }
    return array->len;
}

size_t array_find(Array *array, bool (*pred)(void *)) {
    for (size_t i = 0; i < array->len; ++i) {
        if (pred(array->data[i])) {
            return i;
        }
    }
    return array->len;
}

void *array_assign(Array *array, size_t index, void *data) {
    if (index >= array->len) {
        return NULL;
    }
    void *old = array->data[index];
    array->data[index] = data;
    return old;
}

void array_foreach(Array *array, void (*visit)(void *)) {
    for (size_t i = 0; i < array->len; ++i) {
        visit(array->data[i]);
    }
}

bool array_empty(Array *array) {
    return array->len == 0;
}

void array_free(Array *array) {
    free(array->data);
    free(array);
}
