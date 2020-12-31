//
// Created by sea on 2019/11/27.
//

#include "coll/list.h"

#include <stdlib.h>

typedef struct coll_list_node Node;

struct coll_list_node {
    void *data;
    Node *prev, *next;
};

struct coll_list {
    Node *head;
    size_t len;
};

static void list_insert_node(List *list, Node *node, Node *pos) {
    Node *next = pos->next;
    pos->next = node;
    node->prev = pos;
    node->next = next;
    next->prev = node;
    ++(list->len);
}

static void list_remove_node(List *list, Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    --(list->len);
}

static Node *list_node_of(List *list, void *data) {
    Node *cur = list->head->next;
    while (cur != list->head) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

static Node *list_node_at(List *list, size_t index) {
    size_t index_r = list->len - index - 1;
    if (index_r < index) {
        Node *cur = list->head->prev;
        for (size_t i = 0; i < index_r; ++i) {
            cur = cur->prev;
        }
        return cur;
    }
    Node *cur = list->head->next;
    for (size_t i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
}

List *list_new() {
    List *list = malloc(sizeof(List));
    list->len = 0;
    Node *node = malloc(sizeof(Node));
    list->head = node->prev = node->next = node;
    node->data = NULL;
    return list;
}

void *list_append(List *list, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    list_insert_node(list, node, list->head->prev);
    return data;
}

void *list_prepend(List *list, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    list_insert_node(list, node, list->head);
    return data;
}

void *list_first(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->next->data;
}

void *list_last(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->prev->data;
}

void *list_at(List *list, size_t index) {
    if (index >= list->len) {
        return NULL;
    }
    return list_node_at(list, index)->data;
}

size_t list_size(List *list) {
    if (!list) {
        return 0;
    }
    return list->len;
}

bool list_empty(List *list) {
    return list_size(list) == 0;
}

size_t list_index_of(List *list, void *data) {
    size_t index = 0;
    Node *cur = list->head->next;
    while (cur != list->head) {
        if (cur->data == data) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

size_t list_find(List *list, bool (*pred)(void *)) {
    size_t index = 0;
    Node *cur = list->head->next;
    while (cur != list->head) {
        if (pred(cur->data)) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

void *list_remove(List *list, void *data) {
    Node *node = list_node_of(list, data);
    if (node) {
        list_remove_node(list, node);
        return data;
    }
    return NULL;
}

size_t list_remove_all(List *list, void *data) {
    Node *node;
    size_t count = 0;
    while ((node = list_node_of(list, data)) != NULL) {
        list_remove_node(list, node);
        ++count;
    }
    return count;
}

void *list_remove_if(List *list, bool (*pred)(void *)) {
    Node *cur = list->head->next;
    while (cur != list->head) {
        if (pred(cur->data)) {
            void *data = cur->data;
            list_remove_node(list, cur);
            return data;
        }
        cur = cur->next;
    }
    return NULL;
}

void *list_remove_first(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    void *data = list_first(list);
    list_remove_node(list, list->head->next);
    return data;
}

void *list_remove_last(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    void *data = list_last(list);
    list_remove_node(list, list->head->prev);
    return data;
}

void *list_remove_at(List *list, size_t index) {
    Node *node = list_node_at(list, index);
    if (node) {
        void *data = node->data;
        list_remove_node(list, node);
        return data;
    }
    return NULL;
}

void *list_insert_before(List *list, void *data, void *pos) {
    Node *p = list_node_of(list, pos);
    if (!p) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    list_insert_node(list, node, p->prev);
    return node->data;
}

void *list_insert_after(List *list, void *data, void *pos) {
    Node *p = list_node_of(list, pos);
    if (!p) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    list_insert_node(list, node, p);
    return node->data;
}

void *list_insert_at(List *list, void *data, size_t index) {
    if (!list || index > list->len) {
        return NULL;
    } else if (index == list->len) {
        return list_append(list, data);
    }
    Node *pos = list_node_at(list, index);
    if (!pos) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->data = data;
    list_insert_node(list, node, pos->prev);
    return node->data;
}

void *list_insert_sorted(List *list, void *data, int (*cmp)(void *, void *)) {
    Node *cur = list->head->next;

    if (cur == list->head) {
        return list_append(list, data);
    }

    Node *node = malloc(sizeof(Node));
    node->data = data;

    int result = cmp(data, cur->data);
    while ((cur->next != list->head) && (result > 0)) {
        cur = cur->next;
        result = cmp(data, cur->data);
    }

    if ((cur->next == list->head) && (result > 0)) {
        list_insert_node(list, node, cur);
        return data;
    }

    list_insert_node(list, node, cur->prev);
    return data;
}

void *list_assign(List *list, size_t index, void *data) {
    if (index >= list->len) {
        return NULL;
    }
    Node *pos = list_node_at(list, index);
    void *old = pos->data;
    pos->data = data;
    return old;
}

void list_foreach(List *list, void (*visit)(void *)) {
    Node *cur = list->head->next;
    while (cur != list->head) {
        visit(cur->data);
        cur = cur->next;
    }
}

void list_reverse(List *list) {
    if (list->len == 0 || list->len == 1) {
        return;
    }
    Node *cur = list->head->next, *next;
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
    Node *cur = list->head->next;
    while (cur != list->head) {
        Node *next = cur->next;
        list_remove_node(list, cur);
        cur = next;
    }
}

void list_free(List *list) {
    list_clear(list);
    free(list->head);
    free(list);
}
