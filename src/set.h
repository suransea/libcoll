//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_SET_H
#define LIBCOLL_SET_H

#include <stdbool.h>

typedef struct _set Set;

Set *set_new();

bool set_put(Set *set, void *data);

bool set_contains(Set *set, void *data);

#endif //LIBCOLL_SET_H
