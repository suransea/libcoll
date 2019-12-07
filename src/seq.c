//
// Created by sea on 2019/12/2.
//

#include <stdlib.h>
#include "seq.h"

Seq *seq_append(Seq *seq, void *data) {
    Seq *node = malloc(sizeof(Seq));
    node->data = data;
    node->next = NULL;
    if (seq) {
        Seq *last = seq_last(seq);
        last->next = node;
        return seq;
    }
    return node;
}

Seq *seq_prepend(Seq *seq, void *data) {
    Seq *node = malloc(sizeof(Seq));
    node->data = data;
    node->next = seq;
    return node;
}

void *seq_first(Seq *seq) {
    if (seq) {
        return seq->data;
    }
    return NULL;
}

void *seq_last(Seq *seq) {
    if (!seq) {
        return NULL;
    }
    while (seq->next) {
        seq = seq->next;
    }
    return seq->data;
}

void *seq_at(Seq *seq, size_t index) {
    for (size_t i = 0; i < index; ++i) {
        if (!seq) {
            return NULL;
        }
        seq = seq->next;
    }
    return seq ? seq->data : NULL;
}

size_t seq_index_of(Seq *seq, void *data) {
    size_t index = 0;
    while (seq) {
        if (seq->data == data) {
            return index;
        }
        seq = seq->next;
        ++index;
    }
    return index;
}

size_t seq_find(Seq *seq, bool (*pred)(void *)) {
    size_t index = 0;
    while (seq) {
        if (pred(seq->data)) {
            return index;
        }
        seq = seq->next;
        ++index;
    }
    return index;
}

size_t seq_size(Seq *seq) {
    if (!seq)return 0;
    int len = 0;
    while (seq) {
        ++len;
        seq = seq->next;
    }
    return len;
}

Seq *seq_remove(Seq *seq, void *data) {
    Seq *prev = NULL, *cur = seq;
    while (cur) {
        Seq *next = cur->next;
        if (cur->data == data) {
            if (!prev) {
                free(cur);
                return next;
            }
            prev->next = next;
            free(cur);
            break;
        }
        prev = cur;
        cur = next;
    }
    return seq;
}

Seq *seq_remove_all(Seq *seq, void *data) {
    Seq *prev = NULL, *cur = seq;
    while (cur) {
        Seq *next = cur->next;
        if (cur->data == data) {
            if (!prev) {
                free(cur);
                return next;
            }
            prev->next = next;
            free(cur);
        }
        prev = cur;
        cur = next;
    }
    return seq;
}

Seq *seq_remove_if(Seq *seq, bool (*pred)(void *)) {
    Seq *prev = NULL, *cur = seq;
    while (cur) {
        Seq *next = cur->next;
        if (pred(cur->data)) {
            if (!prev) {
                free(cur);
                return next;
            }
            prev->next = next;
            free(cur);
            break;
        }
        prev = cur;
        cur = next;
    }
    return seq;
}

Seq *seq_remove_at(Seq *seq, size_t index) {
    Seq *prev = NULL, *cur = seq;
    for (size_t i = 0; i < index; ++i) {
        if (!cur) {
            return seq;
        }
        prev = cur;
        cur = cur->next;
    }
    if (!cur) {
        return seq;
    }
    if (!prev) {
        Seq *next = cur->next;
        free(cur);
        return next;
    }
    prev->next = cur->next;
    free(cur);
    return seq;
}

Seq *seq_remove_first(Seq *seq) {
    Seq *next = seq->next;
    free(seq);
    return next;
}

Seq *seq_remove_last(Seq *seq) {
    Seq *cur = seq, *prev = NULL;
    if (cur) {
        while (cur->next) {
            prev = cur;
            cur = cur->next;
        }
        free(cur);
        if (prev) {
            prev->next = NULL;
        } else {
            return NULL;
        }
    }
    return seq;
}

Seq *seq_insert_sorted(Seq *seq, void *data, int(*cmp)(void *, void *)) {
    Seq *cur = seq, *prev = NULL;

    Seq *node = malloc(sizeof(Seq));
    node->data = data;
    node->next = NULL;

    if (!seq) {
        return node;
    }

    int result = cmp(data, cur->data);
    while ((cur->next) && (result > 0)) {
        prev = cur;
        cur = cur->next;

        result = cmp(data, cur->data);
    }

    if ((!cur->next) && (result > 0)) {
        cur->next = node;
        return seq;
    }

    if (prev) {
        prev->next = node;
        node->next = cur;
        return seq;
    } else {
        node->next = seq;
        return node;
    }
}

void seq_foreach(Seq *seq, void(*visit)(void *)) {
    while (seq) {
        Seq *next = seq->next;
        visit(seq->data);
        seq = next;
    }
}

void seq_free(Seq *seq) {
    while (seq) {
        Seq *next = seq->next;
        free(seq);
        seq = next;
    }
}
