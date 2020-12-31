//
// Created by sea on 2019/12/2.
//

#include "coll/hmap.h"

#include <stdlib.h>
#include <string.h>

typedef struct coll_hmap_entry Entry;

struct coll_hmap_entry {
    void *key, *val;
    Entry *next;
    unsigned hash;
};

struct coll_hmap {
    Entry **entries;
    size_t size;
    size_t cap;
    unsigned (*hash)(void *key);
    bool (*equal)(void *, void *);
};

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

static void hmap_resize(HMap *map) {
    if (map->cap == MAX_CAP) {
        return;
    }
    size_t cap_new = map->cap * 2;
    Entry **entries = calloc(cap_new, sizeof(Entry *));
    for (int i = 0; i < map->cap; ++i) {
        Entry *entry = map->entries[i];
        while (entry) {
            Entry *next = entry->next;
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

static void hmap_insert_entry(HMap *map, int index, void *key, void *value, unsigned hash) {
    Entry *old = map->entries[index];
    Entry *entry = malloc(sizeof(Entry));
    entry->key = key;
    entry->val = value;
    entry->hash = hash;
    entry->next = old;
    map->entries[index] = entry;
    if (++(map->size) >= map->cap * LOAD_FACTOR) {
        hmap_resize(map);
    }
}

static Entry *hmap_entry_of(HMap *map, void *key) {
    unsigned hash = hash_key(key, map->hash);
    size_t index = hash & (map->cap - 1);
    Entry *entry = map->entries[index];
    while (entry) {
        if (hash == entry->hash && (key == entry->key || map->equal(key, entry->key))) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

HMap *hmap_new(size_t cap) {
    return hmap_new_custom(cap, hash_ptr, equal_ptr);
}

HMap *hmap_new_custom(size_t cap, unsigned (*hash)(void *), bool (*equal)(void *, void *)) {
    HMap *map = malloc(sizeof(HMap));
    map->cap = prime_cap(cap);
    map->entries = calloc(map->cap, sizeof(Entry *));
    map->size = 0;
    map->hash = hash;
    map->equal = equal;
    return map;
}

void *hmap_insert(HMap *map, void *key, void *value) {
    unsigned hash = hash_key(key, map->hash);
    size_t index = hash & (map->cap - 1);
    Entry *entry = map->entries[index];
    while (entry) {
        if (hash == entry->hash && (key == entry->key || map->equal(key, entry->key))) {
            void *old = entry->val;
            entry->val = value;
            return old;
        }
        entry = entry->next;
    }
    hmap_insert_entry(map, index, key, value, hash);
    return NULL;
}

void *hmap_value_of(HMap *map, void *key) {
    Entry *entry = hmap_entry_of(map, key);
    if (entry) {
        return entry->val;
    }
    return NULL;
}

Seq *hmap_keys(HMap *map) {
    Seq *seq = seq_new();
    for (int i = 0; i < map->cap; ++i) {
        Entry *entry = map->entries[i];
        while (entry) {
            seq_prepend(seq, entry->key);
            entry = entry->next;
        }
    }
    return seq;
}

Seq *hmap_values(HMap *map) {
    Seq *seq = seq_new();
    for (int i = 0; i < map->cap; ++i) {
        Entry *entry = map->entries[i];
        while (entry) {
            seq_prepend(seq, entry->val);
            entry = entry->next;
        }
    }
    return seq;
}

size_t hmap_size(HMap *map) {
    return map->size;
}

bool hmap_empty(HMap *map) {
    return map->size == 0;
}

bool hmap_contains_key(HMap *map, void *key) {
    Entry *entry = hmap_entry_of(map, key);
    return entry != NULL;
}

bool hmap_contains_value(HMap *map, void *value) {
    for (int i = 0; i < map->cap; ++i) {
        Entry *entry = map->entries[i];
        while (entry) {
            if (entry->val == value) {
                return true;
            }
            entry = entry->next;
        }
    }
    return false;
}

void *hmap_remove(HMap *map, void *key) {
    unsigned hash = hash_key(key, map->hash);
    size_t index = hash & (map->cap - 1);
    Entry *entry = map->entries[index], *prev = NULL;
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

void hmap_clear(HMap *map) {
    for (int i = 0; i < map->cap; ++i) {
        Entry *entry = map->entries[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry);
            --(map->size);
            entry = next;
        }
    }
}

void hmap_foreach(HMap *map, void (*visit)(void *, void *)) {
    for (int i = 0; i < map->cap; ++i) {
        Entry *entry = map->entries[i];
        while (entry) {
            Entry *next = entry->next;
            visit(entry->key, entry->val);
            entry = next;
        }
    }
}

void hmap_free(HMap *map) {
    hmap_clear(map);
    free(map->entries);
    free(map);
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
