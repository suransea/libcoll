//
// Created by sea on 2019/12/2.
//

#include "coll/hmap.h"

#include <stdlib.h>
#include <string.h>

typedef struct coll_hmap_entry entry_t;

const static size_t MAX_CAP = 1u << 30u;  // for unsigned, maximum of powers of 2

const static double LOAD_FACTOR = 0.75;

static size_t prime_cap(size_t cap) {
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

static unsigned hash_key(void *key, unsigned (*hash)(void *)) {
    unsigned h = 0u;
    if (key) {
        h = hash(key);
        h ^= h >> 16u;
    }
    return h;
}

static void coll_hmap_resize(coll_hmap_t *map) {
    if (map->cap == MAX_CAP) {
        return;
    }
    size_t cap_new = map->cap * 2;
    entry_t **entries = calloc(cap_new, sizeof(entry_t *));
    for (int i = 0; i < map->cap; ++i) {
        entry_t *entry = map->entries[i];
        while (entry) {
            entry_t *next = entry->next;
            size_t index = entry->hash & (cap_new - 1);
            entry->next = entries[index];
            entries[index] = entry;
            entry = next;
        }
    }
    free(map->entries);
    map->entries = entries;
    map->cap = cap_new;
}

static void coll_hmap_insert_entry(coll_hmap_t *map, int index, void *key, void *value, unsigned hash) {
    entry_t *old = map->entries[index];
    entry_t *entry = malloc(sizeof(entry_t));
    entry->key = key;
    entry->val = value;
    entry->hash = hash;
    entry->next = old;
    map->entries[index] = entry;
    if (++(map->size) >= map->cap * LOAD_FACTOR) {
        coll_hmap_resize(map);
    }
}

static entry_t *coll_hmap_entry_of(coll_hmap_t *map, void *key) {
    unsigned hash = hash_key(key, map->hash);
    size_t index = hash & (map->cap - 1);
    entry_t *entry = map->entries[index];
    while (entry) {
        if (hash == entry->hash && (key == entry->key || map->equal(key, entry->key))) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

void coll_hmap_init(coll_hmap_t *map, size_t cap) {
    coll_hmap_init_custom(map, cap, coll_hash_ptr, coll_equal_ptr);
}

void coll_hmap_init_custom(coll_hmap_t *map, size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *)) {
    map->cap = prime_cap(cap);
    map->entries = calloc(map->cap, sizeof(entry_t *));
    map->size = 0;
    map->hash = hash;
    map->equal = equal;
}

void *coll_hmap_insert(coll_hmap_t *map, void *key, void *value) {
    unsigned hash = hash_key(key, map->hash);
    size_t index = hash & (map->cap - 1);
    entry_t *entry = map->entries[index];
    while (entry) {
        if (hash == entry->hash && (key == entry->key || map->equal(key, entry->key))) {
            void *old = entry->val;
            entry->val = value;
            return old;
        }
        entry = entry->next;
    }
    coll_hmap_insert_entry(map, index, key, value, hash);
    return NULL;
}

void *coll_hmap_value_of(coll_hmap_t *map, void *key) {
    entry_t *entry = coll_hmap_entry_of(map, key);
    if (entry) {
        return entry->val;
    }
    return NULL;
}

coll_seq_t coll_hmap_keys(coll_hmap_t *map) {
    coll_seq_t seq;
    coll_seq_init(&seq);
    for (int i = 0; i < map->cap; ++i) {
        entry_t *entry = map->entries[i];
        while (entry) {
            coll_seq_prepend(&seq, entry->key);
            entry = entry->next;
        }
    }
    return seq;
}

coll_seq_t coll_hmap_values(coll_hmap_t *map) {
    coll_seq_t seq;
    coll_seq_init(&seq);
    for (int i = 0; i < map->cap; ++i) {
        entry_t *entry = map->entries[i];
        while (entry) {
            coll_seq_prepend(&seq, entry->val);
            entry = entry->next;
        }
    }
    return seq;
}

size_t coll_hmap_size(coll_hmap_t *map) {
    return map->size;
}

bool coll_hmap_empty(coll_hmap_t *map) {
    return map->size == 0;
}

bool coll_hmap_contains_key(coll_hmap_t *map, void *key) {
    entry_t *entry = coll_hmap_entry_of(map, key);
    return entry != NULL;
}

bool coll_hmap_contains_value(coll_hmap_t *map, void *value) {
    for (int i = 0; i < map->cap; ++i) {
        entry_t *entry = map->entries[i];
        while (entry) {
            if (entry->val == value) {
                return true;
            }
            entry = entry->next;
        }
    }
    return false;
}

void *coll_hmap_remove(coll_hmap_t *map, void *key) {
    unsigned hash = hash_key(key, map->hash);
    size_t index = hash & (map->cap - 1);
    entry_t *entry = map->entries[index], *prev = NULL;
    while (entry) {
        if (hash == entry->hash && (key == entry->key || map->equal(key, entry->key))) {
            void *val = entry->val;
            if (prev == NULL) {
                map->entries[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            --(map->size);
            return val;
        }
        prev = entry;
        entry = entry->next;
    }
    return NULL;
}

void coll_hmap_clear(coll_hmap_t *map) {
    for (int i = 0; i < map->cap; ++i) {
        entry_t *entry = map->entries[i];
        while (entry) {
            entry_t *next = entry->next;
            free(entry);
            --(map->size);
            entry = next;
        }
    }
}

void coll_hmap_foreach(coll_hmap_t *map, void (*visit)(void *, void *)) {
    for (int i = 0; i < map->cap; ++i) {
        entry_t *entry = map->entries[i];
        while (entry) {
            entry_t *next = entry->next;
            visit(entry->key, entry->val);
            entry = next;
        }
    }
}

void coll_hmap_free(coll_hmap_t *map) {
    coll_hmap_clear(map);
    free(map->entries);
}

// hash and equal functions

unsigned coll_hash_ptr(void *val) {
    return (unsigned) val;
}

unsigned coll_hash_int(void *val) {
    return *(int *) val;
}

unsigned coll_hash_char(void *val) {
    return *(char *) val;
}

unsigned coll_hash_str(void *val) {
    unsigned h = 0;
    size_t len = strlen(val);
    for (int i = 0; i < len; ++i) {
        h = h * 31 + *(char *) val;
    }
    return h;
}

unsigned coll_hash_double(void *val) {
    return (unsigned) *(double *) val;
}

bool coll_equal_ptr(void *x, void *y) {
    return x == y;
}

bool coll_equal_int(void *x, void *y) {
    return *(int *) x == *(int *) y;
}

bool coll_equal_char(void *x, void *y) {
    return *(char *) x == *(char *) y;
}

bool coll_equal_str(void *x, void *y) {
    return strcmp(x, y) == 0;
}

bool coll_equal_double(void *x, void *y) {
    return *(double *) x == *(double *) y;
}
