//
// Created by sea on 2019/11/29.
//

#include "coll/deque.h"

#include <stdlib.h>
#include <string.h>

struct coll_deque {
    void **data;
    size_t len, cap, head, tail;
};

static inline size_t pos_prev(size_t pos, size_t cap) {
    return pos == 0 ? cap - 1 : pos - 1;
}

static inline size_t pos_next(size_t pos, size_t cap) {
    return pos == cap - 1 ? 0 : pos + 1;
}

static inline size_t index_to_pos(coll_deque_t *deque, size_t index) {
    return (deque->head + index) % deque->cap;
}

static void coll_deque_reserve(coll_deque_t *d, size_t p, bool left) {
    if (left) {
        if (p >= d->head) {
            // ---head---pos---tail--- || ---tail---head---pos---
            if (d->head == 0) {
                d->data[d->cap - 1] = d->data[0];
                memmove(d->data, d->data + 1, p * sizeof(void *));
            } else {
                memmove(d->data + d->head - 1, d->data + d->head, (p - d->head + 1) * sizeof(void *));
            }
        } else {
            // ---pos---tail---head---
            memmove(d->data + d->head - 1, d->data + d->head, (d->cap - d->head) * sizeof(void *));
            d->data[d->cap - 1] = d->data[0];
            memmove(d->data, d->data + 1, p * sizeof(void *));
        }
        d->head = pos_prev(d->head, d->cap);
    } else {
        if (p < d->tail) {
            // ---head---pos---tail--- || ---pos---tail---head---
            memmove(d->data + p + 1, d->data + p, (d->tail - p) * sizeof(void *));
        } else {
            // ---tail---head---pos---
            memmove(d->data + 1, d->data, d->tail * sizeof(void *));
            d->data[0] = d->data[d->cap - 1];
            memmove(d->data + p + 1, d->data + p, (d->cap - p - 1) * sizeof(void *));
        }
        d->tail = pos_next(d->tail, d->cap);
    }
}

static void coll_deque_release(coll_deque_t *d, size_t p, bool left) {
    if (left) {
        if (p >= d->head) {
            // ---head---pos---tail--- || ---tail---head---pos---
            memmove(d->data + d->head + 1, d->data + d->head, (p - d->head) * sizeof(void *));
        } else {
            // ---pos---tail---head---
            memmove(d->data + 1, d->data, (p - 1) * sizeof(void *));
            d->data[0] = d->data[d->cap - 1];
            memmove(d->data + d->head + 1, d->data + d->head, (d->cap - d->head - 1) * sizeof(void *));
        }
        d->head = pos_next(d->head, d->cap);
    } else {
        if (p < d->tail) {
            // ---head---pos---tail--- || ---pos---tail---head---
            memmove(d->data + p, d->data + p + 1, (d->tail - p - 1) * sizeof(void *));
        } else {
            // ---tail---head---pos---
            memmove(d->data + p, d->data + p + 1, (d->cap - p - 1) * sizeof(void *));
            d->data[d->cap - 1] = d->data[0];
            memmove(d->data, d->data + 1, (d->tail - 1) * sizeof(void *));
        }
        d->tail = pos_prev(d->tail, d->cap);
    }
}

static void coll_deque_resize(coll_deque_t *deque) {
    size_t cap_new = deque->cap * 2;
    void **tmp = malloc(cap_new * sizeof(void *));

    if (deque->head < deque->tail) {
        // not crossed, copy middle
        memcpy(tmp + deque->head, deque->data + deque->head, (deque->tail - deque->head) * sizeof(void *));
    } else {
        size_t pos_head_new = cap_new - (deque->cap - deque->head);

        // copy end
        memcpy(tmp + pos_head_new, deque->data + deque->head, (deque->cap - deque->head) * sizeof(void *));

        // copy start
        memcpy(tmp, deque->data, deque->tail * sizeof(void *));

        deque->head = pos_head_new;
    }
    free(deque->data);
    deque->data = tmp;
    deque->cap = cap_new;
}

coll_deque_t *coll_deque_new(size_t cap) {
    if (cap == 0) {
        cap = 1;
    }
    coll_deque_t *deque = malloc(sizeof(coll_deque_t));
    deque->data = malloc(cap * sizeof(void *));
    deque->cap = cap;
    deque->len = deque->head = deque->tail = 0;
    return deque;
}

void *coll_deque_append(coll_deque_t *deque, void *data) {
    if (deque->len == deque->cap) {
        coll_deque_resize(deque);
    }
    deque->data[deque->tail] = data;
    deque->tail = pos_next(deque->tail, deque->cap);
    ++(deque->len);
    return data;
}

void *coll_deque_prepend(coll_deque_t *deque, void *data) {
    if (deque->len == deque->cap) {
        coll_deque_resize(deque);
    }
    deque->head = pos_prev(deque->head, deque->cap);
    deque->data[deque->head] = data;
    ++(deque->len);
    return data;
}

size_t coll_deque_size(coll_deque_t *deque) {
    return deque->len;
}

void *coll_deque_first(coll_deque_t *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    return deque->data[deque->head];
}

void *coll_deque_last(coll_deque_t *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    return deque->data[pos_prev(deque->tail, deque->cap)];
}

void *coll_deque_at(coll_deque_t *deque, size_t index) {
    if (index >= deque->len) {
        return NULL;
    }
    return deque->data[index_to_pos(deque, index)];
}

size_t coll_deque_index_of(coll_deque_t *deque, void *data) {
    for (size_t i = 0; i < deque->len; ++i) {
        if (deque->data[index_to_pos(deque, i)] == data) {
            return i;
        }
    }
    return deque->len;
}

size_t coll_deque_find(coll_deque_t *deque, bool (*pred)(void *)) {
    for (size_t i = 0; i < deque->len; ++i) {
        if (pred(deque->data[index_to_pos(deque, i)])) {
            return i;
        }
    }
    return deque->len;
}

void *coll_deque_assign(coll_deque_t *deque, size_t index, void *data) {
    if (index >= deque->len) {
        return NULL;
    }
    size_t pos = index_to_pos(data, index);
    void *old = deque->data[pos];
    deque->data[pos] = data;
    return old;
}

void *coll_deque_insert_at(coll_deque_t *deque, void *data, size_t index) {
    if (index > deque->len) {
        return NULL;
    } else if (index == deque->len) {
        return coll_deque_append(deque, data);
    }
    if (deque->len == deque->cap) {
        coll_deque_resize(deque);
    }

    size_t pos = index_to_pos(deque, index);

    if (index < deque->len / 2) {
        coll_deque_reserve(deque, pos, true);
        deque->data[--pos] = data;
    } else {
        coll_deque_reserve(deque, pos, false);
        deque->data[pos] = data;
    }
    ++(deque->len);
    return data;
}

void *coll_deque_insert_before(coll_deque_t *deque, void *data, void *pos) {
    size_t index = coll_deque_index_of(deque, pos);
    if (index >= deque->len) {
        return NULL;
    }
    return coll_deque_insert_at(deque, data, index);
}

void *coll_deque_insert_after(coll_deque_t *deque, void *data, void *pos) {
    size_t index = coll_deque_index_of(deque, pos);
    if (index >= deque->len) {
        return NULL;
    }
    return coll_deque_insert_at(deque, data, index + 1);
}

void *coll_deque_remove(coll_deque_t *deque, void *data) {
    size_t index = coll_deque_index_of(deque, data);
    return coll_deque_remove_at(deque, index);
}

size_t coll_deque_remove_all(coll_deque_t *deque, void *data) {
    size_t index;
    size_t count = 0;
    while ((index = coll_deque_index_of(deque, data)) < deque->len) {
        coll_deque_remove_at(deque, index);
        ++count;
    }
    return count;
}

void *coll_deque_remove_if(coll_deque_t *deque, bool (*pred)(void *)) {
    size_t index = coll_deque_find(deque, pred);
    return coll_deque_remove_at(deque, index);
}

void *coll_deque_remove_at(coll_deque_t *deque, size_t index) {
    if (!deque || index >= deque->len) {
        return NULL;
    }

    size_t pos = index_to_pos(deque, index);
    void *data = deque->data[pos];

    if (index < deque->len / 2) {
        coll_deque_release(deque, pos, true);
    } else {
        coll_deque_release(deque, pos, false);
    }
    --(deque->len);
    return data;
}

void *coll_deque_remove_first(coll_deque_t *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    void *data = deque->data[deque->head];
    deque->head = pos_next(deque->head, deque->cap);
    --(deque->len);
    return data;
}

void *coll_deque_remove_last(coll_deque_t *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    deque->tail = pos_prev(deque->tail, deque->cap);
    --(deque->len);
    return deque->data[deque->tail];
}

void coll_deque_foreach(coll_deque_t *deque, void (*visit)(void *)) {
    for (size_t i = 0; i < deque->len; ++i) {
        visit(deque->data[index_to_pos(deque, i)]);
    }
}

bool coll_deque_empty(coll_deque_t *deque) {
    return deque->len == 0;
}

void coll_deque_clear(coll_deque_t *deque) {
    deque->len = 0;
    deque->tail = deque->head;
}

void coll_deque_free(coll_deque_t *deque) {
    free(deque->data);
    free(deque);
}
