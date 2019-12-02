//
// Created by sea on 2019/11/27.
//

#ifndef LIBCOLL_LIST_H
#define LIBCOLL_LIST_H

#include <stdbool.h>

typedef struct _list List;

List *list_new();

void *list_append(List *list, void *data);

void *list_prepend(List *list, void *data);

void *list_front(List *list);

void *list_back(List *list);

void *list_at(List *list, int index);

size_t list_len(List *list);

int list_index_of(List *list, void *data);

int list_find(List *list, bool (*pred)(void *));

void *list_remove(List *list, void *data);

size_t list_remove_all(List *list, void *data);

size_t list_remove_if(List *list, bool (*pred)(void *));

void *list_remove_front(List *list);

void *list_remove_back(List *list);

void *list_remove_at(List *list, int index);

void *list_insert_before(List *list, void *data, void *pos);

void *list_insert_after(List *list, void *data, void *pos);

void *list_insert_at(List *list, void *data, int index);

void *list_insert_sorted(List *list, void *data, int(*cmp)(void *, void *));

void list_foreach(List *list, void(*visit)(void *));

void list_sort(List *list, int(*cmp)(void *, void *));

void list_reverse(List *list);

void list_clear(List *list);

void list_free(List *list);

#endif //LIBCOLL_LIST_H
