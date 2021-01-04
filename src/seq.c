//
// Created by sea on 2019/12/2.
//

#include "coll/seq.h"

#include <stdlib.h>

typedef struct coll_seq_node node_t;

struct coll_seq {
    node_t *head;
    size_t len;
};

struct coll_seq_node {
    void *data;
    node_t *next;
};

static node_t *coll_seq_last_node(coll_seq_t *seq) {
    node_t *cur = seq->head;
    if (!cur) {
        return NULL;
    }
    while (cur->next) {
        cur = cur->next;
    }
    return cur;
}

static node_t *coll_seq_node_at(coll_seq_t *seq, size_t index) {
    node_t *cur = seq->head;
    for (size_t i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
}

coll_seq_t *coll_seq_new() {
    coll_seq_t *seq = malloc(sizeof(coll_seq_t));
    seq->len = 0;
    seq->head = NULL;
    return seq;
}

void *coll_seq_append(coll_seq_t *seq, void *data) {
    if (!seq) {
        return NULL;
    }
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    if (seq->head) {
        node_t *last = coll_seq_last_node(seq);
        last->next = node;
        ++(seq->len);
        return data;
    }
    seq->head = node;
    ++(seq->len);
    return data;
}

void *coll_seq_prepend(coll_seq_t *seq, void *data) {
    if (!seq) {
        return NULL;
    }
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->next = seq->head;
    seq->head = node;
    ++(seq->len);
    return data;
}

void *coll_seq_first(coll_seq_t *seq) {
    if (seq && seq->head) {
        return seq->head->data;
    }
    return NULL;
}

void *coll_seq_last(coll_seq_t *seq) {
    if (seq && seq->head) {
        node_t *last = coll_seq_last_node(seq);
        return last->data;
    }
    return NULL;
}

void *coll_seq_at(coll_seq_t *seq, size_t index) {
    if (index >= seq->len) {
        return NULL;
    }
    return coll_seq_node_at(seq, index)->data;
}

size_t coll_seq_index_of(coll_seq_t *seq, void *data) {
    size_t index = 0;
    node_t *cur = seq->head;
    while (cur) {
        if (cur->data == data) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

size_t coll_seq_find(coll_seq_t *seq, bool (*pred)(void *)) {
    size_t index = 0;
    node_t *cur = seq->head;
    while (cur) {
        if (pred(cur->data)) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

size_t coll_seq_size(coll_seq_t *seq) {
    if (!seq) {
        return 0;
    }
    return seq->len;
}

bool coll_seq_empty(coll_seq_t *seq) {
    return seq->len == 0;
}

void *coll_seq_remove(coll_seq_t *seq, void *data) {
    node_t *prev = NULL, *cur = seq->head;
    while (cur) {
        node_t *next = cur->next;
        if (cur->data == data) {
            --(seq->len);
            free(cur);
            if (!prev) {
                seq->head = next;
                return data;
            }
            prev->next = next;
            return data;
        }
        prev = cur;
        cur = next;
    }
    return NULL;
}

size_t coll_seq_remove_all(coll_seq_t *seq, void *data) {
    size_t count = 0;
    node_t *prev = NULL, *cur = seq->head;
    while (cur) {
        node_t *next = cur->next;
        if (cur->data == data) {
            if (!prev) {
                seq->head = next;
            } else {
                prev->next = next;
            }
            free(cur);
            --(seq->len);
            ++count;
        } else {
            prev = cur;
        }
        cur = next;
    }
    return count;
}

void *coll_seq_remove_if(coll_seq_t *seq, bool (*pred)(void *)) {
    node_t *prev = NULL, *cur = seq->head;
    while (cur) {
        node_t *next = cur->next;
        if (pred(cur->data)) {
            --(seq->len);
            void *data = cur->data;
            free(cur);
            if (!prev) {
                seq->head = next;
                return data;
            }
            prev->next = next;
            return data;
        }
        prev = cur;
        cur = next;
    }
    return NULL;
}

void *coll_seq_remove_at(coll_seq_t *seq, size_t index) {
    if (!seq || index >= seq->len) {
        return NULL;
    }
    node_t *prev = NULL, *cur = seq->head;
    for (size_t i = 0; i < index; ++i) {
        prev = cur;
        cur = cur->next;
    }
    if (prev) {
        prev->next = cur->next;
    } else {
        seq->head = cur->next;
    }
    void *data = cur->data;
    free(cur);
    --(seq->len);
    return data;
}

void *coll_seq_remove_first(coll_seq_t *seq) {
    if (!seq || seq->len == 0) {
        return NULL;
    }
    void *data = seq->head->data;
    node_t *next = seq->head->next;
    free(seq->head);
    seq->head = next;
    --(seq->len);
    return data;
}

void *coll_seq_remove_last(coll_seq_t *seq) {
    if (!seq || seq->len == 0) {
        return NULL;
    }
    node_t *prev = NULL, *cur = seq->head;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    if (prev) {
        prev->next = NULL;
    } else {
        seq->head = NULL;
    }
    void *data = cur->data;
    free(cur);
    --(seq->len);
    return data;
}

void *coll_seq_insert_at(coll_seq_t *seq, void *data, size_t index) {
    if (!seq || index > seq->len) {
        return NULL;
    } else if (index == seq->len) {
        return coll_seq_append(seq, data);
    }
    node_t *prev = NULL, *cur = seq->head;
    for (size_t i = 0; i < index; ++i) {
        prev = cur;
        cur = cur->next;
    }
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->next = cur;
    if (prev) {
        prev->next = node;
    } else {
        seq->head = node;
    }
    ++(seq->len);
    return data;
}

void *coll_seq_insert_before(coll_seq_t *seq, void *data, void *pos) {
    if (!seq) {
        return NULL;
    }
    node_t *prev = NULL, *cur = seq->head;
    while (cur) {
        if (cur->data == pos) {
            node_t *node = malloc(sizeof(node_t));
            node->data = data;
            node->next = cur;
            if (prev) {
                prev->next = node;
            } else {
                seq->head = node;
            }
            ++(seq->len);
            return data;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}

void *coll_seq_insert_after(coll_seq_t *seq, void *data, void *pos) {
    if (!seq) {
        return NULL;
    }
    node_t *cur = seq->head;
    while (cur) {
        if (cur->data == pos) {
            node_t *node = malloc(sizeof(node_t));
            node->data = data;
            node->next = cur->next;
            cur->next = node;
            ++(seq->len);
            return data;
        }
        cur = cur->next;
    }
    return NULL;
}

void *coll_seq_insert_sorted(coll_seq_t *seq, void *data, int (*cmp)(void *, void *)) {
    if (!seq) {
        return NULL;
    }

    node_t *prev = NULL, *cur = seq->head;

    if (!cur) {
        return coll_seq_prepend(seq, data);
    }

    node_t *node = malloc(sizeof(node_t));
    node->data = data;

    int result = cmp(data, cur->data);
    while ((cur->next) && (result > 0)) {
        prev = cur;
        cur = cur->next;

        result = cmp(data, cur->data);
    }

    if ((!cur->next) && (result > 0)) {
        cur->next = node;
        node->next = NULL;
        return data;
    }

    if (prev) {
        prev->next = node;
        node->next = cur;
        return data;
    } else {
        seq->head = node;
        node->next = seq->head;
        return data;
    }
}

void *coll_seq_assign(coll_seq_t *seq, size_t index, void *data) {
    if (index >= seq->len) {
        return NULL;
    }
    node_t *pos = coll_seq_node_at(seq, index);
    void *old = pos->data;
    pos->data = data;
    return old;
}

void coll_seq_foreach(coll_seq_t *seq, void (*visit)(void *)) {
    node_t *cur = seq->head;
    while (cur) {
        node_t *next = cur->next;
        visit(cur->data);
        cur = next;
    }
}

void coll_seq_clear(coll_seq_t *seq) {
    while (seq->head) {
        coll_seq_remove_first(seq);
    }
}

void coll_seq_reverse(coll_seq_t *seq) {
    node_t *prev = NULL, *cur = seq->head, *next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    seq->head = prev;
}

void coll_seq_free(coll_seq_t *seq) {
    coll_seq_clear(seq);
    free(seq);
}
