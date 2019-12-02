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
    LNode *next = pos->next;
    pos->next = node;
    node->prev = pos;
    node->next = next;
    next->prev = node;
    ++(list->len);
}

static void _list_remove(List *list, LNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    --(list->len);
}

static LNode *_list_pos(List *list, void *data) {
    LNode *cur = list->head->next;
    while (cur != list->head) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

static LNode *_list_at(List *list, int index) {
    LNode *cur = list->head->next;
    for (int i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
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
    LNode *cur = list->head->next;
    while (cur != list->head) {
        if (cur->data == data) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return -1;
}

int list_find(List *list, bool (*pred)(void *)) {
    int index = 0;
    LNode *cur = list->head->next;
    while (cur != list->head) {
        if (pred(cur->data)) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return -1;
}

void *list_remove(List *list, void *data) {
    LNode *node = _list_pos(list, data);
    if (node) {
        _list_remove(list, node);
        return data;
    }
    return NULL;
}

size_t list_remove_all(List *list, void *data) {
    LNode *node;
    size_t count = 0;
    while ((node = _list_pos(list, data)) != NULL) {
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
    LNode *p = _list_pos(list, pos);
    if (!p) {
        return NULL;
    }
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, p->prev);
    return node;
}

void *list_insert_after(List *list, void *data, void *pos) {
    LNode *p = _list_pos(list, pos);
    if (!p) {
        return NULL;
    }
    LNode *node = malloc(sizeof(LNode));
    node->data = data;
    _list_insert(list, node, p);
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
    LNode *cur = list->head->next;

    if (cur == list->head) {
        return list_append(list, data);
    }

    LNode *node = malloc(sizeof(LNode));
    node->data = data;

    int result = cmp(data, cur->data);
    while ((cur->next != list->head) && (result > 0)) {
        cur = cur->next;
        result = cmp(data, cur->data);
    }

    if ((cur->next == list->head) && (result > 0)) {
        _list_insert(list, node, cur);
        return data;
    }

    _list_insert(list, node, cur->prev);
    return data;
}

void list_foreach(List *list, void(*visit)(void *)) {
    LNode *cur = list->head->next;
    while (cur != list->head) {
        visit(cur->data);
        cur = cur->next;
    }
}

void list_sort(List *list, int(*cmp)(void *, void *)) {
    List *tmp = list_new();
    LNode *cur = list->head->next;
    while (cur != list->head) {
        LNode *next = cur->next;
        list_insert_sorted(tmp, cur->data, cmp);
        _list_remove(list, cur);
        cur = next;
    }
    free(list->head);
    list->head = tmp->head;
    list->len = tmp->len;
    free(tmp);
}

void list_reverse(List *list) {
    if (list->len == 0 || list->len == 1) {
        return;
    }
    LNode *cur = list->head->next, *next;
    while (cur != list->head) {
        next = cur->next;
        cur->next = cur->prev;
        cur->prev = next;
        cur = next;
    }
    next = cur->next;
    cur->next = cur->prev;
    cur->prev = next;
}

void list_clear(List *list) {
    LNode *cur = list->head->next;
    while (cur != list->head) {
        LNode *next = cur->next;
        _list_remove(list, cur);
        cur = next;
    }
}

void list_free(List *list) {
    list_clear(list);
    free(list->head);
    free(list);
}
