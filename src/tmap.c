//
// Created by sea on 2019/11/29.
//

#include "coll/tmap.h"

#include <stdlib.h>
#include <string.h>

typedef struct coll_tmap_entry Entry;  // map entry, node of red-black tree

typedef unsigned char Color;  // map entry color

#define RED 0x01u
#define BLACK 0x00u

struct coll_tmap_entry {
    void *key, *val;
    Entry *left, *right, *parent;
    Color color;
};

struct coll_tmap {
    Entry *root;
    size_t size;
    int (*cmp)(void *, void *);
};

static Entry *tmap_entry_of(TMap *map, void *key) {
    Entry *cur = map->root;
    while (cur) {
        int result = map->cmp(key, cur->key);
        if (result < 0) {
            cur = cur->left;
        } else if (result > 0) {
            cur = cur->right;
        } else {
            return cur;
        }
    }
    return NULL;
}

static Entry *entry_new(void *key, void *value, void *parent) {
    Entry *entry = malloc(sizeof(Entry));
    entry->key = key;
    entry->val = value;
    entry->color = BLACK;
    entry->parent = parent;
    entry->left = NULL;
    entry->right = NULL;
    return entry;
}

static Entry *entry_first(Entry *entry) {
    if (!entry) {
        return NULL;
    }
    while (entry->left) {
        entry = entry->left;
    }
    return entry;
}

static Entry *entry_last(Entry *entry) {
    if (!entry) {
        return NULL;
    }
    while (entry->right) {
        entry = entry->right;
    }
    return entry;
}

static Entry *entry_prev(Entry *entry) {
    if (!entry) {
        return NULL;
    }
    if (entry->left) {
        entry = entry->left;
        while (entry->right) {
            entry = entry->right;
        }
        return entry;
    }
    Entry *prev = entry;
    entry = entry->parent;
    while (entry && entry->left == prev) {
        prev = entry;
        entry = entry->parent;
    }
    return entry;
}

static Entry *entry_next(Entry *entry) {
    if (!entry) {
        return NULL;
    }
    if (entry->right) {
        entry = entry->right;
        while (entry->left) {
            entry = entry->left;
        }
        return entry;
    }
    Entry *prev = entry;
    entry = entry->parent;
    while (entry && entry->right == prev) {
        prev = entry;
        entry = entry->parent;
    }
    return entry;
}

static void entry_rotate_left(TMap *map, Entry *entry) {
    if (!entry) {
        return;
    }
    Entry *r = entry->right;
    entry->right = r->left;
    if (r->left) {
        r->left->parent = entry;
    }
    r->parent = entry->parent;
    if (!entry->parent) {
        map->root = r;
    } else if (entry->parent->left == entry) {
        entry->parent->left = r;
    } else {
        entry->parent->right = r;
    }
    r->left = entry;
    entry->parent = r;
}

static void entry_rotate_right(TMap *map, Entry *entry) {
    if (!entry) {
        return;
    }
    Entry *l = entry->left;
    entry->left = l->right;
    if (l->right) {
        l->right->parent = entry;
    }
    l->parent = entry->parent;
    if (!entry->parent) {
        map->root = l;
    } else if (entry->parent->right == entry) {
        entry->parent->right = l;
    } else {
        entry->parent->left = l;
    }
    l->right = entry;
    entry->parent = l;
}

// inline functions for null safe

static inline Entry *left(Entry *entry) {
    return entry ? entry->left : NULL;
}

static inline Entry *right(Entry *entry) {
    return entry ? entry->right : NULL;
}

static inline Entry *parent(Entry *entry) {
    return entry ? entry->parent : NULL;
}

static inline Color color(Entry *entry) {
    return entry ? entry->color : BLACK;
}

static inline void dye(Entry *entry, Color color) {
    if (entry) {
        entry->color = color;
    }
}

// inline functions end

static void tmap_balance_insert(TMap *map, Entry *entry) {
    dye(entry, RED);
    while (entry && entry != map->root && entry->parent->color == RED) {
        if (parent(entry) == left(parent(parent(entry)))) {
            Entry *e = right(parent(parent(entry)));
            if (color(e) == RED) {
                dye(parent(entry), BLACK);
                dye(e, BLACK);
                dye(parent(parent(entry)), RED);
                entry = parent(parent(entry));
            } else {
                if (entry == right(parent(entry))) {
                    entry = parent(entry);
                    entry_rotate_left(map, entry);
                }
                dye(parent(entry), BLACK);
                dye(parent(parent(entry)), RED);
                entry_rotate_right(map, parent(parent(entry)));
            }
        } else {
            Entry *e = left(parent(parent(entry)));
            if (color(e) == RED) {
                dye(parent(entry), BLACK);
                dye(e, BLACK);
                dye(parent(parent(entry)), RED);
                entry = parent(parent(entry));
            } else {
                if (entry == left(parent(entry))) {
                    entry = parent(entry);
                    entry_rotate_right(map, entry);
                }
                dye(parent(entry), BLACK);
                dye(parent(parent(entry)), RED);
                entry_rotate_left(map, parent(parent(entry)));
            }
        }
    }
    dye(map->root, BLACK);
}

static void tmap_balance_remove(TMap *map, Entry *entry) {
    while (entry != map->root && color(entry) == BLACK) {
        if (entry == left(parent(entry))) {
            Entry *sib = right(parent(entry));  // sibling

            if (color(sib) == RED) {
                dye(sib, BLACK);
                dye(parent(entry), RED);
                entry_rotate_left(map, parent(entry));
                sib = right(parent(entry));
            }

            if (color(left(sib)) == BLACK && color(right(sib)) == BLACK) {
                dye(sib, RED);
                entry = parent(entry);
            } else {
                if (color(right(sib)) == BLACK) {
                    dye(left(sib), BLACK);
                    dye(sib, RED);
                    entry_rotate_right(map, sib);
                    sib = right(parent(entry));
                }
                dye(sib, color(parent(entry)));
                dye(parent(entry), BLACK);
                dye(right(sib), BLACK);
                entry_rotate_left(map, parent(entry));
                entry = map->root;
            }
        } else {
            Entry *sib = left(parent(entry));

            if (color(sib) == RED) {
                dye(sib, BLACK);
                dye(parent(entry), RED);
                entry_rotate_right(map, parent(entry));
                sib = left(parent(entry));
            }

            if (color(right(sib)) == BLACK && color(left(sib)) == BLACK) {
                dye(sib, RED);
                entry = parent(entry);
            } else {
                if (color(left(sib)) == BLACK) {
                    dye(right(sib), BLACK);
                    dye(sib, RED);
                    entry_rotate_left(map, sib);
                    sib = left(parent(entry));
                }
                dye(sib, color(parent(entry)));
                dye(parent(entry), BLACK);
                dye(left(sib), BLACK);
                entry_rotate_right(map, parent(entry));
                entry = map->root;
            }
        }
    }
    dye(entry, BLACK);
}

TMap *tmap_new() {
    return tmap_new_custom(cmp_ptr);
}

TMap *tmap_new_custom(int (*cmp)(void *, void *)) {
    TMap *map = malloc(sizeof(TMap));
    map->size = 0;
    map->cmp = cmp;
    map->root = NULL;
    return map;
}

void *tmap_insert(TMap *map, void *key, void *value) {
    Entry *cur = map->root;
    if (!cur) {
        map->root = entry_new(key, value, NULL);
        ++(map->size);
        return NULL;
    }
    Entry *parent = NULL;
    int result = 0;
    while (cur) {
        parent = cur;
        result = map->cmp(key, cur->key);
        if (result < 0) {
            cur = cur->left;
        } else if (result > 0) {
            cur = cur->right;
        } else {
            void *old = cur->val;
            cur->val = value;
            return old;
        }
    }
    Entry *entry = entry_new(key, value, parent);
    if (result < 0) {
        parent->left = entry;
    } else {
        parent->right = entry;
    }
    tmap_balance_insert(map, entry);
    ++(map->size);
    return NULL;
}

void *tmap_value_of(TMap *map, void *key) {
    Entry *entry = tmap_entry_of(map, key);
    if (entry) {
        return entry->val;
    }
    return NULL;
}

Seq *tmap_keys(TMap *map) {
    Seq *seq = seq_new();
    Entry *cur = entry_last(map->root);
    while (cur) {
        seq_prepend(seq, cur->key);
        cur = entry_prev(cur);
    }
    return seq;
}

Seq *tmap_values(TMap *map) {
    Seq *seq = seq_new();
    Entry *cur = entry_last(map->root);
    while (cur) {
        seq_prepend(seq, cur->val);
        cur = entry_prev(cur);
    }
    return seq;
}

size_t tmap_size(TMap *map) {
    return map->size;
}

bool tmap_empty(TMap *map) {
    return map->size == 0;
}

bool tmap_contains_key(TMap *map, void *key) {
    Entry *entry = tmap_entry_of(map, key);
    return entry != NULL;
}

bool tmap_contains_value(TMap *map, void *value) {
    Entry *cur = entry_first(map->root);
    while (cur) {
        if (cur->val == value) {
            return true;
        }
        cur = entry_next(cur);
    }
    return false;
}

void *tmap_remove(TMap *map, void *key) {
    Entry *entry = tmap_entry_of(map, key);
    if (!entry) {
        return NULL;
    }

    void *old = entry->val;
    if (entry->left && entry->right) {
        Entry *next = entry_next(entry);
        entry->key = next->key;
        entry->val = next->val;
        entry = next;
    }

    // replacement
    Entry *rp = entry->left ? entry->left : entry->right;
    if (rp) {
        rp->parent = entry->parent;
        if (!entry->parent) {
            map->root = rp;
        } else if (entry == entry->parent->left) {
            entry->parent->left = rp;
        } else {
            entry->parent->right = rp;
        }

        if (entry->color == BLACK) {
            tmap_balance_remove(map, rp);
        }
    } else if (!entry->parent) {
        map->root = NULL;
    } else {
        if (entry->color == BLACK) {
            tmap_balance_remove(map, entry);
        }
        if (entry->parent) {
            if (entry == entry->parent->left) {
                entry->parent->left = NULL;
            } else if (entry == entry->parent->right) {
                entry->parent->right = NULL;
            }
        }
    }
    free(entry);
    --(map->size);
    return old;
}

void tmap_clear(TMap *map) {
    Seq *seq = seq_new();
    Entry *cur = entry_last(map->root);
    while (cur) {
        seq_prepend(seq, cur);
        cur = entry_prev(cur);
    }
    seq_foreach(seq, free);
    seq_free(seq);
    map->root = NULL;
    map->size = 0;
}

void tmap_foreach(TMap *map, void (*visit)(void *, void *)) {
    Entry *cur = entry_first(map->root);
    while (cur) {
        Entry *next = entry_next(cur);
        visit(cur->key, cur->val);
        cur = next;
    }
}

void tmap_free(TMap *map) {
    tmap_clear(map);
    free(map);
}


// compare functions

int cmp_ptr(void *x, void *y) {
    size_t m = (size_t) x, n = (size_t) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}

int cmp_int(void *x, void *y) {
    int m = *(int *) x, n = *(int *) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}

int cmp_char(void *x, void *y) {
    char m = *(char *) x, n = *(char *) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}

int cmp_str(void *x, void *y) {
    return strcmp(x, y);
}

int cmp_double(void *x, void *y) {
    double m = *(double *) x, n = *(double *) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}
