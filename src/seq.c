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

Seq *seq_last(Seq *seq) {
    if (seq) {
        while (seq->next)
            seq = seq->next;
    }
    return seq;
}

size_t seq_len(Seq *seq) {
    if (!seq)return 0;
    int len = 0;
    while (seq) {
        ++len;
        seq = seq->next;
    }
    return len;
}

Seq *seq_next(Seq *seq) {
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
