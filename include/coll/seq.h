//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_SEQ_H
#define LIBCOLL_SEQ_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_seq_node coll_seq_node_t;

struct coll_seq_node {
    void *data;
    coll_seq_node_t *next;
};

struct coll_seq {
    coll_seq_node_t *head;
    size_t len;
};

typedef struct coll_seq coll_seq_t;

void coll_seq_init(coll_seq_t *seq);

void *coll_seq_append(coll_seq_t *seq, void *data);

void *coll_seq_prepend(coll_seq_t *seq, void *data);

void *coll_seq_first(coll_seq_t *seq);

void *coll_seq_last(coll_seq_t *seq);

void *coll_seq_at(coll_seq_t *seq, size_t index);

size_t coll_seq_index_of(coll_seq_t *seq, void *data);

size_t coll_seq_find(coll_seq_t *seq, bool (*pred)(void *));

size_t coll_seq_size(coll_seq_t *seq);

bool coll_seq_empty(coll_seq_t *seq);

void *coll_seq_remove(coll_seq_t *seq, void *data);

size_t coll_seq_remove_all(coll_seq_t *seq, void *data);

void *coll_seq_remove_if(coll_seq_t *seq, bool (*pred)(void *));

void *coll_seq_remove_at(coll_seq_t *seq, size_t index);

void *coll_seq_remove_first(coll_seq_t *seq);

void *coll_seq_remove_last(coll_seq_t *seq);

void *coll_seq_insert_at(coll_seq_t *seq, void *data, size_t index);

void *coll_seq_insert_before(coll_seq_t *seq, void *data, void *pos);

void *coll_seq_insert_after(coll_seq_t *seq, void *data, void *pos);

void *coll_seq_insert_sorted(coll_seq_t *seq, void *data, int (*cmp)(void *, void *));

void *coll_seq_assign(coll_seq_t *seq, size_t index, void *data);

void coll_seq_foreach(coll_seq_t *seq, void (*visit)(void *));

void coll_seq_clear(coll_seq_t *seq);

void coll_seq_reverse(coll_seq_t *seq);

void coll_seq_free(coll_seq_t *seq);

#endif  //LIBCOLL_SEQ_H
