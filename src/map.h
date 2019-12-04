//
// Created by sea on 2019/11/29.
//

#ifndef LIBCOLL_MAP_H
#define LIBCOLL_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include "seq.h"

typedef struct _map Map;

Map *map_new();

Map *map_new_custom(int (*cmp)(void *, void *));

void *map_insert(Map *map, void *key, void *value);

void *map_value_of(Map *map, void *key);

Seq *map_keys(Map *map);

Seq *map_values(Map *map);

size_t map_size(Map *map);

bool map_empty(Map *map);

bool map_contains_key(Map *map, void *key);

bool map_contains_value(Map *map, void *value);

void *map_remove(Map *map, void *key);

void map_clear(Map *map);

void map_foreach(Map *map, void(*visit)(void *key, void *value));

void map_free(Map *map);


// compare functions

int cmp_ptr(void *, void *);

int cmp_int(void *, void *);

int cmp_char(void *, void *);

int cmp_str(void *, void *);

int cmp_double(void *, void *);

#endif //LIBCOLL_MAP_H
