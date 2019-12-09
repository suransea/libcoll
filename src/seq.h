//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_SEQ_H
#define LIBCOLL_SEQ_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _seq Seq;

Seq *seq_new();

void *seq_append(Seq *seq, void *data);

void *seq_prepend(Seq *seq, void *data);

void *seq_first(Seq *seq);

void *seq_last(Seq *seq);

void *seq_at(Seq *seq, size_t index);

size_t seq_index_of(Seq *seq, void *data);

size_t seq_find(Seq *seq, bool (*pred)(void *));

size_t seq_size(Seq *seq);

bool seq_empty(Seq *seq);

void *seq_remove(Seq *seq, void *data);

size_t seq_remove_all(Seq *seq, void *data);

void *seq_remove_if(Seq *seq, bool (*pred)(void *));

void *seq_remove_at(Seq *seq, size_t index);

void *seq_remove_first(Seq *seq);

void *seq_remove_last(Seq *seq);

void *seq_insert_at(Seq *seq, void *data, size_t index);

void *seq_insert_before(Seq *seq, void *data, void *pos);

void *seq_insert_after(Seq *seq, void *data, void *pos);

void *seq_insert_sorted(Seq *seq, void *data, int(*cmp)(void *, void *));

void *seq_assign(Seq *seq, size_t index, void *data);

void seq_foreach(Seq *seq, void(*visit)(void *));

void seq_clear(Seq *seq);

void seq_reverse(Seq *seq);

void seq_free(Seq *seq);

#endif //LIBCOLL_SEQ_H
