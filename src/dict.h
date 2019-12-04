//
// Created by sea on 2019/12/2.
//

#ifndef LIBCOLL_DICT_H
#define LIBCOLL_DICT_H

#include <stdbool.h>
#include <stddef.h>
#include "seq.h"

typedef struct _dict Dict;

Dict *dict_new(size_t cap);

Dict *dict_new_custom(size_t cap, unsigned (*hash)(void *key), bool (*equal)(void *, void *));

void *dict_add(Dict *dict, void *key, void *value);

void *dict_value_of(Dict *dict, void *key);

Seq *dict_keys(Dict *dict);

Seq *dict_values(Dict *dict);

size_t dict_size(Dict *dict);

bool dict_empty(Dict *dict);

bool dict_contains_key(Dict *dict, void *key);

bool dict_contains_value(Dict *dict, void *value);

void *dict_remove(Dict *dict, void *key);

void dict_clear(Dict *dict);

void dict_foreach(Dict *dict, void(*visit)(void *key, void *value));

void dict_free(Dict *dict);


// hash and equal functions

unsigned hash_ptr(void *);

unsigned hash_int(void *);

unsigned hash_char(void *);

unsigned hash_str(void *);

unsigned hash_double(void *);

bool equal_ptr(void *, void *);

bool equal_int(void *, void *);

bool equal_char(void *, void *);

bool equal_str(void *, void *);

bool equal_double(void *, void *);

#endif //LIBCOLL_DICT_H
