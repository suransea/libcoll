//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_SEQ_H
#define LIBCOLL_SEQ_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _seq Seq;

struct _seq {
  void *data;
  Seq *next;
};

Seq *seq_append(Seq *seq, void *data);

Seq *seq_prepend(Seq *seq, void *data);

Seq *seq_last(Seq *seq);

size_t seq_size(Seq *seq);

Seq *seq_next(Seq *seq);

Seq *seq_remove_last(Seq *seq);

Seq *seq_insert_sorted(Seq *seq, void *data, int(*cmp)(void *, void *));

void seq_foreach(Seq *seq, void(*visit)(void *));

void seq_free(Seq *seq);

#endif //LIBCOLL_SEQ_H
