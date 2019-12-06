//
// Created by sea on 2019/11/28.
//

#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct _vector {
  void **data;
  size_t len;
  size_t cap;
};

static void _vector_resize(Vector *vector) {
    size_t cap_new = vector->cap * 2;
    void *tmp = realloc(vector->data, cap_new * sizeof(void *));
    vector->data = tmp;
    vector->cap = cap_new;
}

Vector *vector_new(size_t cap) {
    if (cap == 0) {
        cap = 1;
    }
    Vector *vector = malloc(sizeof(Vector));
    vector->data = malloc(cap * sizeof(void *));
    vector->cap = cap;
    vector->len = 0;
    return vector;
}

void *vector_append(Vector *vector, void *data) {
    if (!vector) {
        return NULL;
    }
    if (vector->cap == vector->len) {
        _vector_resize(vector);
    }
    vector->data[vector->len] = data;
    ++(vector->len);
    return data;
}

void *vector_prepend(Vector *vector, void *data) {
    if (!vector) {
        return NULL;
    }
    if (vector->cap == vector->len) {
        size_t cap_new = vector->cap * 2;
        void **tmp = malloc(cap_new * sizeof(void *));
        memcpy(tmp + 1, vector->data, vector->len);
        tmp[0] = data;
        free(vector->data);
        vector->data = tmp;
        vector->cap = cap_new;
        ++(vector->len);
        return data;
    }
    memmove(vector->data + 1, vector->data, vector->len);
    vector->data[0] = data;
    ++(vector->len);
    return data;
}

size_t vector_size(Vector *vector) {
    return vector->len;
}

void *vector_at(Vector *vector, size_t index) {
    if (index >= vector->len) {
        return NULL;
    }
    return vector->data[index];
}

long vector_index_of(Vector *vector, void *data) {
    for (long i = 0; i < vector->len; ++i) {
        if (vector->data[i] == data) {
            return i;
        }
    }
    return -1;
}

long vector_find(Vector *vector, bool (*pred)(void *)) {
    for (long i = 0; i < vector->len; ++i) {
        if (pred(vector->data[i])) {
            return i;
        }
    }
    return -1;
}

void *vector_insert_at(Vector *vector, void *data, size_t index) {
    if (!vector) {
        return NULL;
    }
    if (index >= vector->len) {
        return NULL;
    }
    if (vector->cap == vector->len) {
        size_t cap_new = vector->cap * 2;
        void **tmp = malloc(cap_new * sizeof(void *));
        memcpy(tmp, vector->data, index);
        tmp[index] = data;
        memcpy(tmp + index + 1, vector->data + index, vector->len - index);
        free(vector->data);
        vector->data = tmp;
        vector->cap = cap_new;
        ++(vector->len);
        return data;
    }
    memmove(vector->data + index + 1, vector->data + index, vector->len);
    vector->data[index] = data;
    ++(vector->len);
    return data;
}

void *vector_insert_before(Vector *vector, void *data, void *pos) {
    long index = vector_index_of(vector, pos);
    if (index == -1) {
        return NULL;
    }
    return vector_insert_at(vector, data, index);
}

void *vector_insert_after(Vector *vector, void *data, void *pos) {
    long index = vector_index_of(vector, pos);
    if (index == -1) {
        return NULL;
    }
    if (index == vector->len - 1) {
        return vector_append(vector, data);
    }
    return vector_insert_at(vector, data, index + 1);
}

void *vector_assign(Vector *vector, size_t index, void *data) {
    if (index >= vector->len) {
        return NULL;
    }
    void *old = vector->data[index];
    vector->data[index] = data;
    return old;
}

void vector_foreach(Vector *vector, void(*visit)(void *)) {
    for (int i = 0; i < vector->len; ++i) {
        visit(vector->data[i]);
    }
}

bool vector_empty(Vector *vector) {
    return vector->len == 0;
}

void *vector_remove_last(Vector *vector) {
    if (vector_empty(vector)) {
        return NULL;
    }
    void *data = vector->data[vector->len - 1];
    --(vector->len);
    return data;
}

void vector_clear(Vector *vector) {
    vector->len = 0;
}

void vector_free(Vector *vector) {
    free(vector->data);
    free(vector);
}
