//
// Created by sea on 2019/12/2.
//

#include "coll/seq.h"

#include <stdlib.h>

typedef struct coll_seq_node Node;

struct coll_seq {
    Node *head;
    size_t len;
};

struct coll_seq_node {
    void *data;
    Node *next;
};

static Node *seq_last_node(Seq *seq) {
    Node *cur = seq->head;
    if (!cur) {
        return NULL;
    }
    while (cur->next) {
        cur = cur->next;
    }
    return cur;
}

static Node *seq_node_at(Seq *seq, size_t index) {
    Node *cur = seq->head;
    for (size_t i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
}

Seq *seq_new() {
    Seq *seq = malloc(sizeof(Seq));
    seq->len = 0;
    seq->head = NULL;
    return seq;
}

void *seq_append(Seq *seq, void *data) {
    if (!seq) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (seq->head) {
        Node *last = seq_last_node(seq);
        last->next = node;
        ++(seq->len);
        return data;
    }
    seq->head = node;
    ++(seq->len);
    return data;
}

void *seq_prepend(Seq *seq, void *data) {
    if (!seq) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = seq->head;
    seq->head = node;
    ++(seq->len);
    return data;
}

void *seq_first(Seq *seq) {
    if (seq && seq->head) {
        return seq->head->data;
    }
    return NULL;
}

void *seq_last(Seq *seq) {
    if (seq && seq->head) {
        Node *last = seq_last_node(seq);
        return last->data;
    }
    return NULL;
}

void *seq_at(Seq *seq, size_t index) {
    if (index >= seq->len) {
        return NULL;
    }
    return seq_node_at(seq, index)->data;
}

size_t seq_index_of(Seq *seq, void *data) {
    size_t index = 0;
    Node *cur = seq->head;
    while (cur) {
        if (cur->data == data) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

size_t seq_find(Seq *seq, bool (*pred)(void *)) {
    size_t index = 0;
    Node *cur = seq->head;
    while (cur) {
        if (pred(cur->data)) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

size_t seq_size(Seq *seq) {
    if (!seq) {
        return 0;
    }
    return seq->len;
}

bool seq_empty(Seq *seq) {
    return seq->len == 0;
}

void *seq_remove(Seq *seq, void *data) {
    Node *prev = NULL, *cur = seq->head;
    while (cur) {
        Node *next = cur->next;
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

size_t seq_remove_all(Seq *seq, void *data) {
    size_t count = 0;
    Node *prev = NULL, *cur = seq->head;
    while (cur) {
        Node *next = cur->next;
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

void *seq_remove_if(Seq *seq, bool (*pred)(void *)) {
    Node *prev = NULL, *cur = seq->head;
    while (cur) {
        Node *next = cur->next;
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

void *seq_remove_at(Seq *seq, size_t index) {
    if (!seq || index >= seq->len) {
        return NULL;
    }
    Node *prev = NULL, *cur = seq->head;
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

void *seq_remove_first(Seq *seq) {
    if (!seq || seq->len == 0) {
        return NULL;
    }
    void *data = seq->head->data;
    Node *next = seq->head->next;
    free(seq->head);
    seq->head = next;
    --(seq->len);
    return data;
}

void *seq_remove_last(Seq *seq) {
    if (!seq || seq->len == 0) {
        return NULL;
    }
    Node *prev = NULL, *cur = seq->head;
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

void *seq_insert_at(Seq *seq, void *data, size_t index) {
    if (!seq || index > seq->len) {
        return NULL;
    } else if (index == seq->len) {
        return seq_append(seq, data);
    }
    Node *prev = NULL, *cur = seq->head;
    for (size_t i = 0; i < index; ++i) {
        prev = cur;
        cur = cur->next;
    }
    Node *node = malloc(sizeof(Node));
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

void *seq_insert_before(Seq *seq, void *data, void *pos) {
    if (!seq) {
        return NULL;
    }
    Node *prev = NULL, *cur = seq->head;
    while (cur) {
        if (cur->data == pos) {
            Node *node = malloc(sizeof(Node));
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

void *seq_insert_after(Seq *seq, void *data, void *pos) {
    if (!seq) {
        return NULL;
    }
    Node *cur = seq->head;
    while (cur) {
        if (cur->data == pos) {
            Node *node = malloc(sizeof(Node));
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

void *seq_insert_sorted(Seq *seq, void *data, int (*cmp)(void *, void *)) {
    if (!seq) {
        return NULL;
    }

    Node *prev = NULL, *cur = seq->head;

    if (!cur) {
        return seq_prepend(seq, data);
    }

    Node *node = malloc(sizeof(Node));
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

void *seq_assign(Seq *seq, size_t index, void *data) {
    if (index >= seq->len) {
        return NULL;
    }
    Node *pos = seq_node_at(seq, index);
    void *old = pos->data;
    pos->data = data;
    return old;
}

void seq_foreach(Seq *seq, void (*visit)(void *)) {
    Node *cur = seq->head;
    while (cur) {
        Node *next = cur->next;
        visit(cur->data);
        cur = next;
    }
}

void seq_clear(Seq *seq) {
    while (seq->head) {
        seq_remove_first(seq);
    }
}

void seq_reverse(Seq *seq) {
    Node *prev = NULL, *cur = seq->head, *next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    seq->head = prev;
}

void seq_free(Seq *seq) {
    seq_clear(seq);
    free(seq);
}
