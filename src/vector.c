//
// Created by sea on 2019/11/28.
//

#include <stdlib.h>
#include "vector.h"

Vector *vector_new(size_t cap) {
    Vector *vector = malloc(sizeof(Vector));
    vector->data = malloc(cap * sizeof(void *));
    vector->cap = cap;
    vector->len = 0;
    return vector;
}

void vector_append(Vector *vector, void *data) {
    if (!vector) {
        return;
    }
    if (vector->cap == vector->len) {
        size_t cap_new = vector->cap * 2;
        void *tmp = realloc(vector->data, cap_new * sizeof(void *));
        vector->data = tmp;
        vector->cap = cap_new;
    }
    vector->data[vector->len] = data;
    ++(vector->len);
}

void *vector_at(Vector *vector, int index) {
    if (index >= vector->len) {
        return NULL;
    }
    return vector->data[index];
}

void vector_set(Vector *vector, int index, void *data) {
    if (index >= vector->len) {
        return;
    }
    vector->data[index] = data;
}

void vector_foreach(Vector *vector, void(*visit)(void *)) {
    for (int i = 0; i < vector->len; ++i) {
        visit(vector->data[i]);
    }
}
