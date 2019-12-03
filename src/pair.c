//
// Created by sea on 2019/12/3.
//

#include <stdlib.h>
#include "pair.h"

Pair *pair_new(void *first, void *second) {
    Pair *pair = malloc(sizeof(Pair));
    pair->first = first;
    pair->second = second;
    return pair;
}

void pair_free(Pair *pair) {
    free(pair);
}
