//
// Created by sea on 2019/11/27.
//

#ifndef LIBCOLL_LIST_H
#define LIBCOLL_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_list_node coll_list_node_t;

struct coll_list_node {
    void *data;
    coll_list_node_t *prev, *next;
};

struct coll_list {
    coll_list_node_t *head;
    size_t len;
};

typedef struct coll_list coll_list_t;

void coll_list_init(coll_list_t *list);

void *coll_list_append(coll_list_t *list, void *data);

void *coll_list_prepend(coll_list_t *list, void *data);

void *coll_list_first(coll_list_t *list);

void *coll_list_last(coll_list_t *list);

void *coll_list_at(coll_list_t *list, size_t index);

size_t coll_list_size(coll_list_t *list);

bool coll_list_empty(coll_list_t *list);

size_t coll_list_index_of(coll_list_t *list, void *data);

size_t coll_list_find(coll_list_t *list, bool (*pred)(void *));

void *coll_list_remove(coll_list_t *list, void *data);

size_t coll_list_remove_all(coll_list_t *list, void *data);

void *coll_list_remove_if(coll_list_t *list, bool (*pred)(void *));

void *coll_list_remove_first(coll_list_t *list);

void *coll_list_remove_last(coll_list_t *list);

void *coll_list_remove_at(coll_list_t *list, size_t index);

void *coll_list_insert_before(coll_list_t *list, void *data, void *pos);

void *coll_list_insert_after(coll_list_t *list, void *data, void *pos);

void *coll_list_insert_at(coll_list_t *list, void *data, size_t index);

void *coll_list_insert_sorted(coll_list_t *list, void *data, int (*cmp)(void *, void *));

void *coll_list_assign(coll_list_t *list, size_t index, void *data);

void coll_list_foreach(coll_list_t *list, void (*visit)(void *));

void coll_list_reverse(coll_list_t *list);

void coll_list_clear(coll_list_t *list);

void coll_list_free(coll_list_t *list);

#endif  // LIBCOLL_LIST_H
