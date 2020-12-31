//
// Created by sea on 2019/11/27.
//

#ifndef LIBCOLL_LIST_H
#define LIBCOLL_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct coll_list List;

List *list_new();

void *list_append(List *list, void *data);

void *list_prepend(List *list, void *data);

void *list_first(List *list);

void *list_last(List *list);

void *list_at(List *list, size_t index);

size_t list_size(List *list);

bool list_empty(List *list);

size_t list_index_of(List *list, void *data);

size_t list_find(List *list, bool (*pred)(void *));

void *list_remove(List *list, void *data);

size_t list_remove_all(List *list, void *data);

void *list_remove_if(List *list, bool (*pred)(void *));

void *list_remove_first(List *list);

void *list_remove_last(List *list);

void *list_remove_at(List *list, size_t index);

void *list_insert_before(List *list, void *data, void *pos);

void *list_insert_after(List *list, void *data, void *pos);

void *list_insert_at(List *list, void *data, size_t index);

void *list_insert_sorted(List *list, void *data, int (*cmp)(void *, void *));

void *list_assign(List *list, size_t index, void *data);

void list_foreach(List *list, void (*visit)(void *));

void list_reverse(List *list);

void list_clear(List *list);

void list_free(List *list);

#endif  // LIBCOLL_LIST_H
