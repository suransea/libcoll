//
// Created by sea on 2019/11/27.
//

#include <stdlib.h>
#include "list.h"

void _list_insert(List *list, Node *node, Node *pos) {
    Node *tmp = pos->next;
    pos->next = node;
    node->prev = pos;
    node->next = tmp;
    tmp->prev = node;
    ++(list->len);
}

void _list_remove(List *list, Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    --(list->len);
}

List *list_new() {
    List *list = malloc(sizeof(List));
    list->len = 0;
    Node *node = malloc(sizeof(Node));
    list->head = node->prev = node->next = node;
    node->data = NULL;
    return list;
}

Node *list_append(List *list, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    _list_insert(list, node, list->head->prev);
    return node;
}

Node *list_prepend(List *list, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    _list_insert(list, node, list->head);
    return node;
}

Node *list_front(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->next;
}

Node *list_back(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->prev;
}

Node *list_at(List *list, int index) {
    if (index >= list->len) {
        return NULL;
    }
    Node *tmp = list->head->next;
    for (int i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp;
}

Node *list_find(List *list, void *data) {
    Node *tmp = list->head->next;
    while (tmp != list->head) {
        if (tmp->data == data) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

size_t list_len(List *list) {
    return list->len;
}

int list_index(List *list, void *data) {
    int index = 0;
    Node *tmp = list->head->next;
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
    Node *node = list_find(list, data);
    if (node) {
        _list_remove(list, node);
        return data;
    }
    return NULL;
}

size_t list_remove_all(List *list, void *data) {
    Node *node;
    size_t count = 0;
    while ((node = list_find(list, data)) != NULL) {
        _list_remove(list, node);
        ++count;
    }
    return count;
}

void *list_remove_at(List *list, int index) {
    Node *node = list_at(list, index);
    if (node) {
        _list_remove(list, node);
        return node->data;
    }
    return NULL;
}

Node *list_insert_before(List *list, void *data, Node *pos) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    _list_insert(list, node, pos->prev);
    return node;
}

Node *list_insert_after(List *list, void *data, Node *pos) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    _list_insert(list, node, pos);
    return node;
}

Node *list_insert_at(List *list, void *data, int index) {
    Node *pos = list_at(list, index);
    if (pos) {
        return list_insert_before(list, data, pos);
    }
    return NULL;
}

Node *list_insert_sorted(List *list, void *data, int(*cmp)(void *, void *)) {
    Node *tmp = list->head->next;

    if (tmp == list->head) {
        return list_append(list, data);
    }

    Node *node = malloc(sizeof(Node));
    node->data = data;

    int result = cmp(data, tmp->data);
    while ((tmp->next != list->head) && (result > 0)) {
        tmp = tmp->next;
        result = cmp(data, tmp->data);
    }

    if ((tmp->next == list->head) && (result > 0)) {
        return list_insert_after(list, data, tmp);
    }

    return list_insert_before(list, data, tmp);
}

void list_foreach(List *list, void(*visit)(void *)) {
    Node *tmp = list->head->next;
    while (tmp != list->head) {
        visit(tmp->data);
        tmp = tmp->next;
    }
}

void list_sort(List *list, int(*cmp)(void *, void *)) {
    //TODO
}

void list_clear(List *list) {
    Node *tmp = list->head->next;
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
