//
// Created by sea on 2019/11/27.
//

#ifndef LIBCOLL_LIST_H
#define LIBCOLL_LIST_H

typedef struct _node Node;
typedef struct _list List;

struct _node {
  void *data;
  Node *prev, *next;
};

struct _list {
  Node *head;
  size_t len;
};

List *list_new();

Node *list_append(List *list, void *data);

Node *list_prepend(List *list, void *data);

Node *list_front(List *list);

Node *list_back(List *list);

Node *list_at(List *list, int index);

Node *list_find(List *list, void *data);

size_t list_len(List *list);

int list_index(List *list, void *data);

void* list_remove(List *list, void *data);

size_t list_remove_all(List *list, void *data);

void* list_remove_at(List *list, int index);

Node* list_insert_before(List *list, void *data, Node *pos);

Node* list_insert_after(List *list, void *data, Node *pos);

Node* list_insert_at(List *list, void *data, int index);

Node* list_insert_sorted(List *list, void *data, int(*cmp)(void *, void *));

void list_foreach(List *list, void(*visit)(void *));

void list_sort(List *list, int(*cmp)(void *, void *));

void list_clear(List *list);

void list_free(List *list);

#endif //LIBCOLL_LIST_H
