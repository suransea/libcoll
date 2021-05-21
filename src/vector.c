//
// Created by sea on 2019/11/28.
//

#include "coll/vector.h"

#include <stdlib.h>
#include <string.h>

static void coll_vector_resize(coll_vector_t *vector) {
    size_t cap_new = vector->cap * 2;
    void *tmp = realloc(vector->data, cap_new * sizeof(void *));
    vector->data = tmp;
    vector->cap = cap_new;
}

void coll_vector_init(coll_vector_t *vector, size_t cap) {
    if (cap == 0) {
        cap = 1;
    }
    vector->data = malloc(cap * sizeof(void *));
    vector->cap = cap;
    vector->len = 0;
}

void *coll_vector_append(coll_vector_t *vector, void *data) {
    if (!vector) {
        return NULL;
    }
    if (vector->cap == vector->len) {
        coll_vector_resize(vector);
    }
    vector->data[vector->len] = data;
    ++(vector->len);
    return data;
}

void *coll_vector_prepend(coll_vector_t *vector, void *data) {
    if (!vector) {
        return NULL;
    }
    if (vector->cap == vector->len) {
        size_t cap_new = vector->cap * 2;
        void **tmp = malloc(cap_new * sizeof(void *));
        memcpy(tmp + 1, vector->data, vector->len * sizeof(void *));
        tmp[0] = data;
        free(vector->data);
        vector->data = tmp;
        vector->cap = cap_new;
        ++(vector->len);
        return data;
    }
    memmove(vector->data + 1, vector->data, vector->len * sizeof(void *));
    vector->data[0] = data;
    ++(vector->len);
    return data;
}

size_t coll_vector_size(coll_vector_t *vector) {
    return vector->len;
}

void *coll_vector_at(coll_vector_t *vector, size_t index) {
    if (!vector || index >= vector->len) {
        return NULL;
    }
    return vector->data[index];
}

void *coll_vector_first(coll_vector_t *vector) {
    if (!vector || vector->len == 0) {
        return NULL;
    }
    return vector->data[0];
}

void *coll_vector_last(coll_vector_t *vector) {
    if (!vector || vector->len == 0) {
        return NULL;
    }
    return vector->data[vector->len - 1];
}

size_t coll_vector_index_of(coll_vector_t *vector, void *data) {
    for (size_t i = 0; i < vector->len; ++i) {
        if (vector->data[i] == data) {
            return i;
        }
    }
    return vector->len;
}

size_t coll_vector_find(coll_vector_t *vector, bool (*pred)(void *)) {
    for (size_t i = 0; i < vector->len; ++i) {
        if (pred(vector->data[i])) {
            return i;
        }
    }
    return vector->len;
}

void *coll_vector_insert_at(coll_vector_t *vector, void *data, size_t index) {
    if (!vector || index > vector->len) {
        return NULL;
    } else if (index == vector->len) {
        return coll_vector_append(vector, data);
    }
    if (vector->cap == vector->len) {
        size_t cap_new = vector->cap * 2;
        void **tmp = malloc(cap_new * sizeof(void *));
        memcpy(tmp, vector->data, index * sizeof(void *));
        tmp[index] = data;
        memcpy(tmp + index + 1, vector->data + index, (vector->len - index) * sizeof(void *));
        free(vector->data);
        vector->data = tmp;
        vector->cap = cap_new;
        ++(vector->len);
        return data;
    }
    memmove(vector->data + index + 1, vector->data + index, (vector->len - index) * sizeof(void *));
    vector->data[index] = data;
    ++(vector->len);
    return data;
}

void *coll_vector_insert_before(coll_vector_t *vector, void *data, void *pos) {
    size_t index = coll_vector_index_of(vector, pos);
    if (index >= vector->len) {
        return NULL;
    }
    return coll_vector_insert_at(vector, data, index);
}

void *coll_vector_insert_after(coll_vector_t *vector, void *data, void *pos) {
    size_t index = coll_vector_index_of(vector, pos);
    if (index >= vector->len) {
        return NULL;
    }
    return coll_vector_insert_at(vector, data, index + 1);
}

void *coll_vector_assign(coll_vector_t *vector, size_t index, void *data) {
    if (index >= vector->len) {
        return NULL;
    }
    void *old = vector->data[index];
    vector->data[index] = data;
    return old;
}

void coll_vector_foreach(coll_vector_t *vector, void (*visit)(void *)) {
    for (size_t i = 0; i < vector->len; ++i) {
        visit(vector->data[i]);
    }
}

bool coll_vector_empty(coll_vector_t *vector) {
    return vector->len == 0;
}

void *coll_vector_remove(coll_vector_t *vector, void *data) {
    size_t index = coll_vector_index_of(vector, data);
    return coll_vector_remove_at(vector, index);
}

size_t coll_vector_remove_all(coll_vector_t *vector, void *data) {
    size_t index;
    size_t count = 0;
    while ((index = coll_vector_index_of(vector, data)) < vector->len) {
        coll_vector_remove_at(vector, index);
        ++count;
    }
    return count;
}

void *coll_vector_remove_if(coll_vector_t *vector, bool (*pred)(void *)) {
    size_t index = coll_vector_find(vector, pred);
    return coll_vector_remove_at(vector, index);
}

void *coll_vector_remove_at(coll_vector_t *vector, size_t index) {
    if (!vector || index >= vector->len) {
        return NULL;
    }
    void *data = vector->data[index];
    if (index < vector->len - 1) {
        memmove(vector->data + index, vector->data + index + 1, (vector->len - index - 1) * sizeof(void *));
    }
    --(vector->len);
    return data;
}

void *coll_vector_remove_first(coll_vector_t *vector) {
    return coll_vector_remove_at(vector, 0);
}

void *coll_vector_remove_last(coll_vector_t *vector) {
    if (!vector || coll_vector_empty(vector)) {
        return NULL;
    }
    void *data = vector->data[vector->len - 1];
    --(vector->len);
    return data;
}

void coll_vector_clear(coll_vector_t *vector) {
    vector->len = 0;
}

void coll_vector_free(coll_vector_t *vector) {
    free(vector->data);
}
