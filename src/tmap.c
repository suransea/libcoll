//
// Created by sea on 2019/11/29.
//

#include "coll/tmap.h"

#include <stdlib.h>
#include <string.h>

typedef struct coll_tmap_entry entry_t;

typedef coll_entry_color_t color_t;

#define RED COLL_ENTRY_COLOR_RED
#define BLACK COLL_ENTRY_COLOR_BLACK

static entry_t *coll_tmap_entry_of(coll_tmap_t *map, void *key) {
    entry_t *cur = map->root;
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

static entry_t *entry_new(void *key, void *value, void *parent) {
    entry_t *entry = malloc(sizeof(entry_t));
    entry->key = key;
    entry->val = value;
    entry->color = BLACK;
    entry->parent = parent;
    entry->left = NULL;
    entry->right = NULL;
    return entry;
}

static entry_t *entry_first(entry_t *entry) {
    if (!entry) {
        return NULL;
    }
    while (entry->left) {
        entry = entry->left;
    }
    return entry;
}

static entry_t *entry_last(entry_t *entry) {
    if (!entry) {
        return NULL;
    }
    while (entry->right) {
        entry = entry->right;
    }
    return entry;
}

static entry_t *entry_prev(entry_t *entry) {
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
    entry_t *prev = entry;
    entry = entry->parent;
    while (entry && entry->left == prev) {
        prev = entry;
        entry = entry->parent;
    }
    return entry;
}

static entry_t *entry_next(entry_t *entry) {
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
    entry_t *prev = entry;
    entry = entry->parent;
    while (entry && entry->right == prev) {
        prev = entry;
        entry = entry->parent;
    }
    return entry;
}

static void entry_rotate_left(coll_tmap_t *map, entry_t *entry) {
    if (!entry) {
        return;
    }
    entry_t *r = entry->right;
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

static void entry_rotate_right(coll_tmap_t *map, entry_t *entry) {
    if (!entry) {
        return;
    }
    entry_t *l = entry->left;
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

static inline entry_t *left(entry_t *entry) {
    return entry ? entry->left : NULL;
}

static inline entry_t *right(entry_t *entry) {
    return entry ? entry->right : NULL;
}

static inline entry_t *parent(entry_t *entry) {
    return entry ? entry->parent : NULL;
}

static inline color_t color(entry_t *entry) {
    return entry ? entry->color : BLACK;
}

static inline void dye(entry_t *entry, color_t color) {
    if (entry) {
        entry->color = color;
    }
}

// inline functions end

static void coll_tmap_balance_insert(coll_tmap_t *map, entry_t *entry) {
    dye(entry, RED);
    while (entry && entry != map->root && entry->parent->color == RED) {
        if (parent(entry) == left(parent(parent(entry)))) {
            entry_t *e = right(parent(parent(entry)));
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
            entry_t *e = left(parent(parent(entry)));
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

static void coll_tmap_balance_remove(coll_tmap_t *map, entry_t *entry) {
    while (entry != map->root && color(entry) == BLACK) {
        if (entry == left(parent(entry))) {
            entry_t *sib = right(parent(entry));  // sibling

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
            entry_t *sib = left(parent(entry));

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

void coll_tmap_init(coll_tmap_t *map) {
    coll_tmap_init_custom(map, coll_cmp_ptr);
}

void coll_tmap_init_custom(coll_tmap_t *map, int (*cmp)(void *, void *)) {
    map->size = 0;
    map->cmp = cmp;
    map->root = NULL;
}

void *coll_tmap_insert(coll_tmap_t *map, void *key, void *value) {
    entry_t *cur = map->root;
    if (!cur) {
        map->root = entry_new(key, value, NULL);
        ++(map->size);
        return NULL;
    }
    entry_t *parent = NULL;
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
    entry_t *entry = entry_new(key, value, parent);
    if (result < 0) {
        parent->left = entry;
    } else {
        parent->right = entry;
    }
    coll_tmap_balance_insert(map, entry);
    ++(map->size);
    return NULL;
}

void *coll_tmap_value_of(coll_tmap_t *map, void *key) {
    entry_t *entry = coll_tmap_entry_of(map, key);
    if (entry) {
        return entry->val;
    }
    return NULL;
}

coll_seq_t coll_tmap_keys(coll_tmap_t *map) {
    coll_seq_t seq;
    coll_seq_init(&seq);
    entry_t *cur = entry_last(map->root);
    while (cur) {
        coll_seq_prepend(&seq, cur->key);
        cur = entry_prev(cur);
    }
    return seq;
}

coll_seq_t coll_tmap_values(coll_tmap_t *map) {
    coll_seq_t seq;
    coll_seq_init(&seq);
    entry_t *cur = entry_last(map->root);
    while (cur) {
        coll_seq_prepend(&seq, cur->val);
        cur = entry_prev(cur);
    }
    return seq;
}

size_t coll_tmap_size(coll_tmap_t *map) {
    return map->size;
}

bool coll_tmap_empty(coll_tmap_t *map) {
    return map->size == 0;
}

bool coll_tmap_contains_key(coll_tmap_t *map, void *key) {
    entry_t *entry = coll_tmap_entry_of(map, key);
    return entry != NULL;
}

bool coll_tmap_contains_value(coll_tmap_t *map, void *value) {
    entry_t *cur = entry_first(map->root);
    while (cur) {
        if (cur->val == value) {
            return true;
        }
        cur = entry_next(cur);
    }
    return false;
}

void *coll_tmap_remove(coll_tmap_t *map, void *key) {
    entry_t *entry = coll_tmap_entry_of(map, key);
    if (!entry) {
        return NULL;
    }

    void *old = entry->val;
    if (entry->left && entry->right) {
        entry_t *next = entry_next(entry);
        entry->key = next->key;
        entry->val = next->val;
        entry = next;
    }

    // replacement
    entry_t *rp = entry->left ? entry->left : entry->right;
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
            coll_tmap_balance_remove(map, rp);
        }
    } else if (!entry->parent) {
        map->root = NULL;
    } else {
        if (entry->color == BLACK) {
            coll_tmap_balance_remove(map, entry);
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

void coll_tmap_clear(coll_tmap_t *map) {
    coll_seq_t seq;
    coll_seq_init(&seq);
    entry_t *cur = entry_last(map->root);
    while (cur) {
        coll_seq_prepend(&seq, cur);
        cur = entry_prev(cur);
    }
    coll_seq_foreach(&seq, free);
    coll_seq_free(&seq);
    map->root = NULL;
    map->size = 0;
}

void coll_tmap_foreach(coll_tmap_t *map, void (*visit)(void *, void *)) {
    entry_t *cur = entry_first(map->root);
    while (cur) {
        entry_t *next = entry_next(cur);
        visit(cur->key, cur->val);
        cur = next;
    }
}

void coll_tmap_free(coll_tmap_t *map) {
    coll_tmap_clear(map);
}


// compare functions

int coll_cmp_ptr(void *x, void *y) {
    size_t m = (size_t) x, n = (size_t) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}

int coll_cmp_int(void *x, void *y) {
    int m = *(int *) x, n = *(int *) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}

int coll_cmp_char(void *x, void *y) {
    char m = *(char *) x, n = *(char *) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}

int coll_cmp_str(void *x, void *y) {
    return strcmp(x, y);
}

int coll_cmp_double(void *x, void *y) {
    double m = *(double *) x, n = *(double *) y;
    return m < n ? -1 : (m > n ? 1 : 0);
}
