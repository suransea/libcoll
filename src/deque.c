//
// Created by sea on 2019/11/29.
//

#include <stdlib.h>
#include <string.h>
#include "deque.h"

struct _deque {
  void **data;
  size_t len, cap, head, tail;
};

static inline size_t _pos_prev(size_t pos, size_t cap) {
    return pos == 0 ? cap - 1 : pos - 1;
}

static inline size_t _pos_next(size_t pos, size_t cap) {
    return pos == cap - 1 ? 0 : pos + 1;
}

static inline size_t _index_to_pos(Deque *deque, size_t index) {
    return (deque->head + index) % deque->cap;
}

static void _deque_reserve(Deque *d, size_t p, char direct) {
    if (direct == 'l') {
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
        d->head = _pos_prev(d->head, d->cap);
    } else if (direct == 'r') {
        if (p < d->tail) {
            // ---head---pos---tail--- || ---pos---tail---head---
            memmove(d->data + p + 1, d->data + p, (d->tail - p) * sizeof(void *));
        } else {
            // ---tail---head---pos---
            memmove(d->data + 1, d->data, d->tail * sizeof(void *));
            d->data[0] = d->data[d->cap - 1];
            memmove(d->data + p + 1, d->data + p, (d->cap - p - 1) * sizeof(void *));
        }
        d->tail = _pos_next(d->tail, d->cap);
    }
}

static void _deque_release(Deque *d, size_t p, char direct) {
    if (direct == 'l') {
        if (p >= d->head) {
            // ---head---pos---tail--- || ---tail---head---pos---
            memmove(d->data + d->head + 1, d->data + d->head, (p - d->head) * sizeof(void *));
        } else {
            // ---pos---tail---head---
            memmove(d->data + 1, d->data, (p - 1) * sizeof(void *));
            d->data[0] = d->data[d->cap - 1];
            memmove(d->data + d->head + 1, d->data + d->head, (d->cap - d->head - 1) * sizeof(void *));
        }
        d->head = _pos_next(d->head, d->cap);
    } else if (direct == 'r') {
        if (p < d->tail) {
            // ---head---pos---tail--- || ---pos---tail---head---
            memmove(d->data + p, d->data + p + 1, (d->tail - p - 1) * sizeof(void *));
        } else {
            // ---tail---head---pos---
            memmove(d->data + p, d->data + p + 1, (d->cap - p - 1) * sizeof(void *));
            d->data[d->cap - 1] = d->data[0];
            memmove(d->data, d->data + 1, (d->tail - 1) * sizeof(void *));
        }
        d->tail = _pos_prev(d->tail, d->cap);
    }
}

static void _deque_resize(Deque *deque) {
    size_t cap_new = deque->cap * 2;
    void **tmp = malloc(cap_new * sizeof(void *));

    if (deque->head < deque->tail) {
        // not crossed, copy middle
        memcpy(tmp + deque->head, deque->data, (deque->tail - deque->head) * sizeof(void *));
    } else {
        size_t pos_head_new = cap_new - (deque->cap - deque->head);

        // copy end
        memcpy(tmp + pos_head_new, deque->data, (deque->cap - deque->head) * sizeof(void *));

        // copy start
        memcpy(tmp, deque->data, deque->tail * sizeof(void *));

        deque->head = pos_head_new;
    }
    free(deque->data);
    deque->data = tmp;
    deque->cap = cap_new;
}

Deque *deque_new(size_t cap) {
    if (cap == 0) {
        cap = 1;
    }
    Deque *deque = malloc(sizeof(Deque));
    deque->data = malloc(cap * sizeof(void *));
    deque->cap = cap;
    deque->len = deque->head = deque->tail = 0;
    return deque;
}

void *deque_append(Deque *deque, void *data) {
    if (deque->len == deque->cap) {
        _deque_resize(deque);
    }
    deque->data[deque->tail] = data;
    deque->tail = _pos_next(deque->tail, deque->cap);
    ++(deque->len);
    return data;
}

void *deque_prepend(Deque *deque, void *data) {
    if (deque->len == deque->cap) {
        _deque_resize(deque);
    }
    deque->head = _pos_prev(deque->head, deque->cap);
    deque->data[deque->head] = data;
    ++(deque->len);
    return data;
}

size_t deque_size(Deque *deque) {
    return deque->len;
}

void *deque_first(Deque *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    return deque->data[deque->head];
}

void *deque_last(Deque *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    return deque->data[_pos_prev(deque->tail, deque->cap)];
}

void *deque_at(Deque *deque, size_t index) {
    if (index >= deque->len) {
        return NULL;
    }
    return deque->data[_index_to_pos(deque, index)];
}

size_t deque_index_of(Deque *deque, void *data) {
    for (size_t i = 0; i < deque->len; ++i) {
        if (deque->data[_index_to_pos(deque, i)] == data) {
            return i;
        }
    }
    return deque->len;
}

size_t deque_find(Deque *deque, bool (*pred)(void *)) {
    for (size_t i = 0; i < deque->len; ++i) {
        if (pred(deque->data[_index_to_pos(deque, i)])) {
            return i;
        }
    }
    return deque->len;
}

void *deque_assign(Deque *deque, size_t index, void *data) {
    if (index >= deque->len) {
        return NULL;
    }
    size_t pos = _index_to_pos(data, index);
    void *old = deque->data[pos];
    deque->data[pos] = data;
    return old;
}

void *deque_insert_at(Deque *deque, void *data, size_t index) {
    if (index > deque->len) {
        return NULL;
    } else if (index == deque->len) {
        return deque_append(deque, data);
    }
    if (deque->len == deque->cap) {
        _deque_resize(deque);
    }

    size_t pos = _index_to_pos(deque, index);

    if (index < deque->len / 2) {
        _deque_reserve(deque, pos, 'l');
        deque->data[--pos] = data;
    } else {
        _deque_reserve(deque, pos, 'r');
        deque->data[pos] = data;
    }
    ++(deque->len);
    return data;
}

void *deque_insert_before(Deque *deque, void *data, void *pos) {
    size_t index = deque_index_of(deque, pos);
    if (index >= deque->len) {
        return NULL;
    }
    return deque_insert_at(deque, data, index);
}

void *deque_insert_after(Deque *deque, void *data, void *pos) {
    size_t index = deque_index_of(deque, pos);
    if (index >= deque->len) {
        return NULL;
    }
    return deque_insert_at(deque, data, index + 1);
}

void *deque_remove(Deque *deque, void *data) {
    size_t index = deque_index_of(deque, data);
    return deque_remove_at(deque, index);
}

size_t deque_remove_all(Deque *deque, void *data) {
    size_t index;
    size_t count = 0;
    while ((index = deque_index_of(deque, data)) < deque->len) {
        deque_remove_at(deque, index);
        ++count;
    }
    return count;
}

void *deque_remove_if(Deque *deque, bool (*pred)(void *)) {
    size_t index = deque_find(deque, pred);
    return deque_remove_at(deque, index);
}

void *deque_remove_at(Deque *deque, size_t index) {
    if (!deque || index >= deque->len) {
        return NULL;
    }

    size_t pos = _index_to_pos(deque, index);
    void *data = deque->data[pos];

    if (index < deque->len / 2) {
        _deque_release(deque, pos, 'l');
    } else {
        _deque_release(deque, pos, 'r');
    }
    --(deque->len);
    return data;
}

void *deque_remove_first(Deque *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    void *data = deque->data[deque->head];
    deque->head = _pos_next(deque->head, deque->cap);
    return data;
}

void *deque_remove_last(Deque *deque) {
    if (deque->len == 0) {
        return NULL;
    }
    deque->tail = _pos_prev(deque->tail, deque->cap);
    return deque->data[deque->tail];
}

void deque_foreach(Deque *deque, void(*visit)(void *)) {
    for (size_t i = 0; i < deque->len; ++i) {
        visit(deque->data[_index_to_pos(deque, i)]);
    }
}

bool deque_empty(Deque *deque) {
    return deque->len == 0;
}

void deque_clear(Deque *deque) {
    deque->len = 0;
    deque->tail = deque->head;
}

void deque_free(Deque *deque) {
    free(deque->data);
    free(deque);
}
