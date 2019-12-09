//
// Created by sea on 2019/12/2.
//

#include <stdlib.h>
#include "seq.h"

typedef struct _s_node Node;

struct _seq {
  Node *root;
  size_t len;
};

struct _s_node {
  void *data;
  Node *next;
};

static Node *_seq_last(Seq *seq) {
    Node *cur = seq->root;
    if (!cur) {
        return NULL;
    }
    while (cur->next) {
        cur = cur->next;
    }
    return cur;
}

static Node *_seq_at(Seq *seq, size_t index) {
    Node *cur = seq->root;
    for (size_t i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
}

Seq *seq_new() {
    Seq *seq = malloc(sizeof(Seq));
    seq->len = 0;
    seq->root = NULL;
    return seq;
}

void *seq_append(Seq *seq, void *data) {
    if (!seq) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (seq->root) {
        Node *last = _seq_last(seq);
        last->next = node;
        ++(seq->len);
        return data;
    }
    seq->root = node;
    ++(seq->len);
    return data;
}

void *seq_prepend(Seq *seq, void *data) {
    if (!seq) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = seq->root;
    seq->root = node;
    ++(seq->len);
    return data;
}

void *seq_first(Seq *seq) {
    if (seq && seq->root) {
        return seq->root->data;
    }
    return NULL;
}

void *seq_last(Seq *seq) {
    if (seq && seq->root) {
        Node *last = _seq_last(seq);
        return last->data;
    }
    return NULL;
}

void *seq_at(Seq *seq, size_t index) {
    if (index >= seq->len) {
        return NULL;
    }
    return _seq_at(seq, index)->data;
}

size_t seq_index_of(Seq *seq, void *data) {
    size_t index = 0;
    Node *cur = seq->root;
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
    Node *cur = seq->root;
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
    Node *prev = NULL, *cur = seq->root;
    while (cur) {
        Node *next = cur->next;
        if (cur->data == data) {
            --(seq->len);
            free(cur);
            if (!prev) {
                seq->root = next;
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
    Node *prev = NULL, *cur = seq->root;
    while (cur) {
        Node *next = cur->next;
        if (cur->data == data) {
            if (!prev) {
                seq->root = next;
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
    Node *prev = NULL, *cur = seq->root;
    while (cur) {
        Node *next = cur->next;
        if (pred(cur->data)) {
            --(seq->len);
            void *data = cur->data;
            free(cur);
            if (!prev) {
                seq->root = next;
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
    Node *prev = NULL, *cur = seq->root;
    for (size_t i = 0; i < index; ++i) {
        prev = cur;
        cur = cur->next;
    }
    if (prev) {
        prev->next = cur->next;
    } else {
        seq->root = cur->next;
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
    void *data = seq->root->data;
    Node *next = seq->root->next;
    free(seq->root);
    seq->root = next;
    --(seq->len);
    return data;
}

void *seq_remove_last(Seq *seq) {
    if (!seq || seq->len == 0) {
        return NULL;
    }
    Node *prev = NULL, *cur = seq->root;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    if (prev) {
        prev->next = NULL;
    } else {
        seq->root = NULL;
    }
    void *data = cur->data;
    free(cur);
    --(seq->len);
    return data;
}

void *seq_insert_at(Seq *seq, void *data, size_t index) {
    if (!seq || index >= seq->len) {
        return NULL;
    }
    Node *prev = NULL, *cur = seq->root;
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
        seq->root = node;
    }
    ++(seq->len);
    return data;
}

void *seq_insert_before(Seq *seq, void *data, void *pos) {
    if (!seq) {
        return NULL;
    }
    Node *prev = NULL, *cur = seq->root;
    while (cur) {
        if (cur->data == pos) {
            Node *node = malloc(sizeof(Node));
            node->data = data;
            node->next = cur;
            if (prev) {
                prev->next = node;
            } else {
                seq->root = node;
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
    Node *cur = seq->root;
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

void *seq_insert_sorted(Seq *seq, void *data, int(*cmp)(void *, void *)) {
    if (!seq) {
        return NULL;
    }

    Node *prev = NULL, *cur = seq->root;

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
        seq->root = node;
        node->next = seq->root;
        return data;
    }
}

void *seq_assign(Seq *seq, size_t index, void *data) {
    if (index >= seq->len) {
        return NULL;
    }
    Node *pos = _seq_at(seq, index);
    void *old = pos->data;
    pos->data = data;
    return old;
}

void seq_foreach(Seq *seq, void(*visit)(void *)) {
    Node *cur = seq->root;
    while (cur) {
        Node *next = cur->next;
        visit(cur->data);
        cur = next;
    }
}

void seq_clear(Seq *seq) {
    while (seq->root) {
        seq_remove_first(seq);
    }
}

void seq_reverse(Seq *seq) {
    Node *prev = NULL, *cur = seq->root, *next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    seq->root = prev;
}

void seq_free(Seq *seq) {
    seq_clear(seq);
    free(seq);
}
