//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_SET_H
#define LIBCOLL_SET_H

#include <stdbool.h>

typedef struct _set Set;

Set *set_new();

bool set_add(Set *set, void *data);

bool set_contains(Set *set, void *data);

size_t set_size(Set *set);

bool set_empty(Set *set);

void set_foreach(Set *set, void(*visit)(void *));

void set_clear(Set *set);

void set_free(Set *set);

#endif //LIBCOLL_SET_H
