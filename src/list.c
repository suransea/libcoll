//
// Created by sea on 2019/11/27.
//

#include <stdlib.h>
#include "list.h"

typedef struct _l_node LNode;

struct _l_node {
  void *data;
  LNode *prev, *next;
};

struct _list {
  LNode *head;
  size_t len;
};

static void _list_insert(List *list, LNode *node, LNode *pos) {
    LNode *tmp = pos->next;
    pos->next = node;
    node->prev = pos;
    node->next = tmp;
    tmp->prev = node;
    ++(list->len);
}

static void _list_remove(List *list, LNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    --(list->len);
}

static LNode *_list_find(List *list, void *data) {
    LNode *tmp = list->head->next;
    while (tmp != list->head) {
        if (tmp->data == data) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

static LNode *_list_at(List *list, int index) {
    LNode *tmp = list->head->next;
    for (int i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp;
}

List *list_new() {
    List *list = malloc(sizeof(List));
    list->len = 0;
    LNode *node = malloc(sizeof(LNode));
    list->head = node->prev = node->next = node;
    node->data = NULL;
    return list;
}

void *list_append(List *list, void *data) {
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, list->head->prev);
    return data;
}

void *list_prepend(List *list, void *data) {
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, list->head);
    return data;
}

void *list_front(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->next->data;
}

void *list_back(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->prev->data;
}

void *list_at(List *list, int index) {
    if (index >= list->len) {
        return NULL;
    }
    return _list_at(list, index)->data;
}

size_t list_len(List *list) {
    if (!list) {
        return 0;
    }
    return list->len;
}

int list_index_of(List *list, void *data) {
    int index = 0;
    LNode *tmp = list->head->next;
    while (tmp != list->head) {
        if (tmp->data == data) {
            return index;
        }
        tmp = tmp->next;
        ++index;
    }
    return -1;
}

void *list_remove(List *list, void *data) {
    LNode *node = _list_find(list, data);
    if (node) {
        _list_remove(list, node);
        return data;
    }
    return NULL;
}

size_t list_remove_all(List *list, void *data) {
    LNode *node;
    size_t count = 0;
    while ((node = _list_find(list, data)) != NULL) {
        _list_remove(list, node);
        ++count;
    }
    return count;
}

size_t list_remove_if(List *list, bool (*pred)(void *)) {
    size_t count = 0;
    LNode *cur = list->head->next;
    while (cur != list->head) {
        LNode *next = cur->next;
        if (pred(cur->data)) {
            _list_remove(list, cur);
            ++count;
        }
        cur = next;
    }
    return count;
}

void *list_remove_front(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    void *data = list_front(list);
    _list_remove(list, list->head->next);
    return data;
}

void *list_remove_back(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    void *data = list_back(list);
    _list_remove(list, list->head->prev);
    return data;
}

void *list_remove_at(List *list, int index) {
    LNode *node = _list_at(list, index);
    if (node) {
        _list_remove(list, node);
        return node->data;
    }
    return NULL;
}

void *list_insert_before(List *list, void *data, void *pos) {
    LNode *find = _list_find(list, pos);
    if (!find) {
        return NULL;
    }
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, find->prev);
    return node;
}

void *list_insert_after(List *list, void *data, void *pos) {
    LNode *find = _list_find(list, pos);
    if (!find) {
        return NULL;
    }
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, find);
    return node;
}

void *list_insert_at(List *list, void *data, int index) {
    LNode *pos = _list_at(list, index);
    if (!pos) {
        return NULL;
    }
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, pos->prev);
    return node;
}

void *list_insert_sorted(List *list, void *data, int(*cmp)(void *, void *)) {
    LNode *tmp = list->head->next;

    if (tmp == list->head) {
        return list_append(list, data);
    }

    LNode *node = malloc(sizeof(LNode));
    node->data = data;

    int result = cmp(data, tmp->data);
    while ((tmp->next != list->head) && (result > 0)) {
        tmp = tmp->next;
        result = cmp(data, tmp->data);
    }

    if ((tmp->next == list->head) && (result > 0)) {
        _list_insert(list, node, tmp);
        return data;
    }

    _list_insert(list, node, tmp->prev);
    return data;
}

void list_foreach(List *list, void(*visit)(void *)) {
    LNode *tmp = list->head->next;
    while (tmp != list->head) {
        visit(tmp->data);
        tmp = tmp->next;
    }
}

void list_sort(List *list, int(*cmp)(void *, void *)) {
    //TODO
}

void list_clear(List *list) {
    LNode *tmp = list->head->next;
    while (tmp != list->head) {
        _list_remove(list, tmp);
        tmp = tmp->next;
    }
}

void list_free(List *list) {
    list_clear(list);
    free(list->head);
    free(list);
}
