//
// Created by sea on 2019/12/2.
//

#include <stdlib.h>
#include "ring.h"

static Ring *_ring_remove(Ring *node) {
    if (!node) {
        return NULL;
    }
    if (node->next == node) {
        free(node);
        return NULL;
    }
    Ring *next = node->next;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return next;
}

Ring *ring_new(size_t len) {
    if (len == 0) {
        return NULL;
    }
    Ring *ring = malloc(sizeof(Ring));
    ring->data = NULL;
    Ring *cur = ring;
    for (int i = 1; i < len; ++i) {
        cur->next = malloc(sizeof(Ring));
        cur->next->prev = cur;
        cur = cur->next;
        cur->data = NULL;
    }
    cur->next = ring;
    ring->prev = cur;
    return ring;
}

Ring *ring_insert(Ring *ring, void *data) {
    Ring *node = malloc(sizeof(Ring));
    node->data = data;
    if (!ring) {
        node->prev = node->next = node;
        return node;
    }
    Ring *next = ring->next;
    node->prev = ring;
    node->next = next;
    ring->next = node;
    next->prev = node;
    return node;
}

Ring *ring_remove(Ring *ring, void *data) {
    if (!ring) {
        return NULL;
    }
    if (ring->data == data) {
        return _ring_remove(ring);
    }
    Ring *cur = ring->next;
    while (cur != ring) {
        if (cur->data == data) {
            return _ring_remove(cur);
        }
        cur = cur->next;
    }
    return ring;
}

Ring *ring_remove_all(Ring *ring, void *data) {
    if (!ring) {
        return NULL;
    }
    if (ring->data == data) {
        ring = _ring_remove(ring);
        if (!ring) {
            return NULL;
        }
    }
    Ring *end = ring, *cur = ring->next;
    while (cur != end) {
        Ring *next = cur->next;
        if (cur->data == data) {
            ring = _ring_remove(cur);
        }
        cur = next;
    }
    return ring;
}

Ring *ring_remove_if(Ring *ring, bool (*pred)(void *)) {
    if (!ring) {
        return NULL;
    }
    if (pred(ring->data)) {
        ring = _ring_remove(ring);
        if (!ring) {
            return NULL;
        }
    }
    Ring *end = ring, *cur = ring->next;
    while (cur != end) {
        Ring *next = cur->next;
        if (pred(cur->data)) {
            ring = _ring_remove(cur);
        }
        cur = next;
    }
    return ring;
}

size_t ring_size(Ring *ring) {
    if (!ring) {
        return 0;
    }
    size_t len = 1;
    Ring *cur = ring->next;
    while (cur != ring) {
        ++len;
        cur = cur->next;
    }
    return len;
}

Ring *ring_move(Ring *ring, int n) {
    Ring *cur = ring;
    if (n < 0) {
        for (int i = 0; i > n; --i) {
            cur = cur->prev;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            cur = cur->next;
        }
    }
    return cur;
}

void ring_foreach(Ring *ring, void(*visit)(void *)) {
    visit(ring->data);
    Ring *cur = ring->next;
    while (cur != ring) {
        Ring *next = cur->next;
        visit(cur->data);
        cur = next;
    }
}

void ring_free(Ring *ring) {
    while (ring) {
        ring = _ring_remove(ring);
    }
}
