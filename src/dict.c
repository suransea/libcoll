//
// Created by sea on 2019/12/2.
//

#include <stdlib.h>
#include <string.h>
#include "dict.h"

typedef struct _entry Entry;

struct _dict {
  Entry **entries;
  size_t size;
  size_t cap;
  unsigned (*hash)(void *key);
  bool (*equal)(void *, void *);
};

struct _entry {
  void *key;
  void *val;
  Entry *next;
  unsigned hash;
};

const static size_t MAX_CAP = 1u << 30u; // for unsigned, maximum of powers of 2

const static double LOAD_FACTOR = 0.75;

static size_t _prime_cap(size_t cap) {
    if (cap == 0) {
        return 1;
    }
    if (cap > MAX_CAP) {
        return MAX_CAP;
    }
    size_t n = cap - 1;
    n |= n >> 1u;
    n |= n >> 2u;
    n |= n >> 4u;
    n |= n >> 8u;
    n |= n >> 16u;
    return n > MAX_CAP ? MAX_CAP : n + 1;
}

static unsigned _hash_key(void *key, unsigned (*hash)(void *)) {
    unsigned h = 0u;
    if (key) {
        h = hash(key);
        h ^= h >> 16u;
    }
    return h;
}

static void _dict_resize(Dict *dict) {
    if (dict->cap == MAX_CAP) {
        return;
    }
    size_t cap_new = dict->cap * 2;
    Entry **entries = calloc(cap_new, sizeof(Entry *));
    for (int i = 0; i < dict->cap; ++i) {
        Entry *entry = dict->entries[i];
        while (entry) {
            Entry *next = entry->next;
            int index = entry->hash & (cap_new - 1);
            entry->next = entries[index];
            entries[index] = entry;
            entry = next;
        }
    }
    free(dict->entries);
    dict->entries = entries;
    dict->cap = cap_new;
}

static void _dict_add_entry(Dict *dict, int index, void *key, void *value, unsigned hash) {
    Entry *old = dict->entries[index];
    Entry *entry = malloc(sizeof(Entry));
    entry->key = key;
    entry->val = value;
    entry->hash = hash;
    entry->next = old;
    dict->entries[index] = entry;
    if (++(dict->size) >= dict->cap * LOAD_FACTOR) {
        _dict_resize(dict);
    }
}

static Entry *_dict_entry_of(Dict *dict, void *key) {
    unsigned hash = _hash_key(key, dict->hash);
    int index = hash & (dict->cap - 1);
    Entry *entry = dict->entries[index];
    while (entry) {
        if (hash == entry->hash &&
            (key == entry->key || dict->equal(key, entry->key))) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

Dict *dict_new(size_t cap) {
    return dict_new_custom(cap, hash_ptr, equal_ptr);
}

Dict *dict_new_custom(size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *)) {
    Dict *dict = malloc(sizeof(Dict));
    dict->cap = _prime_cap(cap);
    dict->entries = calloc(dict->cap, sizeof(Entry *));
    dict->size = 0;
    dict->hash = hash;
    dict->equal = equal;
    return dict;
}

void *dict_add(Dict *dict, void *key, void *value) {
    unsigned hash = _hash_key(key, dict->hash);
    size_t index = hash & (dict->cap - 1);
    Entry *entry = dict->entries[index];
    while (entry) {
        if (hash == entry->hash &&
            (key == entry->key || dict->equal(key, entry->key))) {
            void *old = entry->val;
            entry->val = value;
            return old;
        }
        entry = entry->next;
    }
    _dict_add_entry(dict, index, key, value, hash);
    return NULL;
}

void *dict_value_of(Dict *dict, void *key) {
    Entry *entry = _dict_entry_of(dict, key);
    if (entry) {
        return entry->val;
    }
    return NULL;
}

Seq *dict_keys(Dict *dict) {
    Seq *seq = NULL;
    for (int i = 0; i < dict->cap; ++i) {
        Entry *entry = dict->entries[i];
        while (entry) {
            seq_prepend(seq, entry->key);
            entry = entry->next;
        }
    }
    return seq;
}

Seq *dict_values(Dict *dict) {
    Seq *seq = NULL;
    for (int i = 0; i < dict->cap; ++i) {
        Entry *entry = dict->entries[i];
        while (entry) {
            seq_prepend(seq, entry->val);
            entry = entry->next;
        }
    }
    return seq;
}

size_t dict_size(Dict *dict) {
    return dict->size;
}

bool dict_empty(Dict *dict) {
    return dict->size == 0;
}

bool dict_contains_key(Dict *dict, void *key) {
    Entry *entry = _dict_entry_of(dict, key);
    return entry != NULL;
}

bool dict_contains_value(Dict *dict, void *value) {
    for (int i = 0; i < dict->cap; ++i) {
        Entry *entry = dict->entries[i];
        while (entry) {
            if (entry->val == value) {
                return true;
            }
            entry = entry->next;
        }
    }
    return false;
}

void *dict_remove(Dict *dict, void *key) {
    unsigned hash = _hash_key(key, dict->hash);
    size_t index = hash & (dict->cap - 1);
    Entry *entry = dict->entries[index], *prev = NULL;
    while (entry) {
        if (hash == entry->hash &&
            (key == entry->key || dict->equal(key, entry->key))) {
            void *val = entry->val;
            if (prev == NULL) {
                dict->entries[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            --(dict->size);
            return val;
        }
        prev = entry;
        entry = entry->next;
    }
    return NULL;
}

void dict_clear(Dict *dict) {
    for (int i = 0; i < dict->cap; ++i) {
        Entry *entry = dict->entries[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry);
            --(dict->size);
            entry = next;
        }
    }
}

void dict_foreach(Dict *dict, void(*visit)(void *, void *)) {
    for (int i = 0; i < dict->cap; ++i) {
        Entry *entry = dict->entries[i];
        while (entry) {
            Entry *next = entry->next;
            visit(entry->key, entry->val);
            entry = next;
        }
    }
}

void dict_free(Dict *dict) {
    dict_clear(dict);
    free(dict->entries);
    free(dict);
}

// hash and equal functions

unsigned hash_ptr(void *val) {
    return (unsigned) val;
}

unsigned hash_int(void *val) {
    return *(int *) val;
}

unsigned hash_char(void *val) {
    return *(char *) val;
}

unsigned hash_str(void *val) {
    unsigned h = 0;
    size_t len = strlen(val);
    for (int i = 0; i < len; ++i) {
        h = h * 31 + *(char *) val;
    }
    return h;
}

unsigned hash_double(void *val) {
    return (unsigned) *(double *) val;
}

bool equal_ptr(void *x, void *y) {
    return x == y;
}

bool equal_int(void *x, void *y) {
    return *(int *) x == *(int *) y;
}

bool equal_char(void *x, void *y) {
    return *(char *) x == *(char *) y;
}

bool equal_str(void *x, void *y) {
    return strcmp(x, y) == 0;
}

bool equal_double(void *x, void *y) {
    return *(double *) x == *(double *) y;
}
