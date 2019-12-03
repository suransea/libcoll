//
// Created by sea on 2019/12/3.
//

#ifndef LIBCOLL_PAIR_H
#define LIBCOLL_PAIR_H

typedef struct _pair Pair;

struct _pair {
  void *first;
  void *second;
};

Pair *pair_new(void *first, void *second);

void pair_free(Pair *pair);

#endif //LIBCOLL_PAIR_H
