//
// Created by sea on 2019/11/27.
//

#include "coll/list.h"

#include <stdlib.h>

typedef struct coll_list_node node_t;

static void coll_list_insert_node(coll_list_t *list, node_t *node, node_t *pos) {
    node_t *next = pos->next;
    pos->next = node;
    node->prev = pos;
    node->next = next;
    next->prev = node;
    ++(list->len);
}

static void coll_list_remove_node(coll_list_t *list, node_t *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    --(list->len);
}

static node_t *coll_list_node_of(coll_list_t *list, void *data) {
    node_t *cur = list->head->next;
    while (cur != list->head) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

static node_t *coll_list_node_at(coll_list_t *list, size_t index) {
    size_t index_r = list->len - index - 1;
    if (index_r < index) {
        node_t *cur = list->head->prev;
        for (size_t i = 0; i < index_r; ++i) {
            cur = cur->prev;
        }
        return cur;
    }
    node_t *cur = list->head->next;
    for (size_t i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
}

void coll_list_init(coll_list_t *list) {
    list->len = 0;
    node_t *node = malloc(sizeof(node_t));
    list->head = node->prev = node->next = node;
    node->data = NULL;
}

void *coll_list_append(coll_list_t *list, void *data) {
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    coll_list_insert_node(list, node, list->head->prev);
    return data;
}

void *coll_list_prepend(coll_list_t *list, void *data) {
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    coll_list_insert_node(list, node, list->head);
    return data;
}

void *coll_list_first(coll_list_t *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->next->data;
}

void *coll_list_last(coll_list_t *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->prev->data;
}

void *coll_list_at(coll_list_t *list, size_t index) {
    if (index >= list->len) {
        return NULL;
    }
    return coll_list_node_at(list, index)->data;
}

size_t coll_list_size(coll_list_t *list) {
    if (!list) {
        return 0;
    }
    return list->len;
}

bool coll_list_empty(coll_list_t *list) {
    return coll_list_size(list) == 0;
}

size_t coll_list_index_of(coll_list_t *list, void *data) {
    size_t index = 0;
    node_t *cur = list->head->next;
    while (cur != list->head) {
        if (cur->data == data) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

size_t coll_list_find(coll_list_t *list, bool (*pred)(void *)) {
    size_t index = 0;
    node_t *cur = list->head->next;
    while (cur != list->head) {
        if (pred(cur->data)) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return index;
}

void *coll_list_remove(coll_list_t *list, void *data) {
    node_t *node = coll_list_node_of(list, data);
    if (node) {
        coll_list_remove_node(list, node);
        return data;
    }
    return NULL;
}

size_t coll_list_remove_all(coll_list_t *list, void *data) {
    node_t *node;
    size_t count = 0;
    while ((node = coll_list_node_of(list, data)) != NULL) {
        coll_list_remove_node(list, node);
        ++count;
    }
    return count;
}

void *coll_list_remove_if(coll_list_t *list, bool (*pred)(void *)) {
    node_t *cur = list->head->next;
    while (cur != list->head) {
        if (pred(cur->data)) {
            void *data = cur->data;
            coll_list_remove_node(list, cur);
            return data;
        }
        cur = cur->next;
    }
    return NULL;
}

void *coll_list_remove_first(coll_list_t *list) {
    if (list->len == 0) {
        return NULL;
    }
    void *data = coll_list_first(list);
    coll_list_remove_node(list, list->head->next);
    return data;
}

void *coll_list_remove_last(coll_list_t *list) {
    if (list->len == 0) {
        return NULL;
    }
    void *data = coll_list_last(list);
    coll_list_remove_node(list, list->head->prev);
    return data;
}

void *coll_list_remove_at(coll_list_t *list, size_t index) {
    node_t *node = coll_list_node_at(list, index);
    if (node) {
        void *data = node->data;
        coll_list_remove_node(list, node);
        return data;
    }
    return NULL;
}

void *coll_list_insert_before(coll_list_t *list, void *data, void *pos) {
    node_t *p = coll_list_node_of(list, pos);
    if (!p) {
        return NULL;
    }
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    coll_list_insert_node(list, node, p->prev);
    return node->data;
}

void *coll_list_insert_after(coll_list_t *list, void *data, void *pos) {
    node_t *p = coll_list_node_of(list, pos);
    if (!p) {
        return NULL;
    }
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    coll_list_insert_node(list, node, p);
    return node->data;
}

void *coll_list_insert_at(coll_list_t *list, void *data, size_t index) {
    if (!list || index > list->len) {
        return NULL;
    } else if (index == list->len) {
        return coll_list_append(list, data);
    }
    node_t *pos = coll_list_node_at(list, index);
    if (!pos) {
        return NULL;
    }
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    coll_list_insert_node(list, node, pos->prev);
    return node->data;
}

void *coll_list_insert_sorted(coll_list_t *list, void *data, int (*cmp)(void *, void *)) {
    node_t *cur = list->head->next;

    if (cur == list->head) {
        return coll_list_append(list, data);
    }

    node_t *node = malloc(sizeof(node_t));
    node->data = data;

    int result = cmp(data, cur->data);
    while ((cur->next != list->head) && (result > 0)) {
        cur = cur->next;
        result = cmp(data, cur->data);
    }

    if ((cur->next == list->head) && (result > 0)) {
        coll_list_insert_node(list, node, cur);
        return data;
    }

    coll_list_insert_node(list, node, cur->prev);
    return data;
}

void *coll_list_assign(coll_list_t *list, size_t index, void *data) {
    if (index >= list->len) {
        return NULL;
    }
    node_t *pos = coll_list_node_at(list, index);
    void *old = pos->data;
    pos->data = data;
    return old;
}

void coll_list_foreach(coll_list_t *list, void (*visit)(void *)) {
    node_t *cur = list->head->next;
    while (cur != list->head) {
        visit(cur->data);
        cur = cur->next;
    }
}

void coll_list_reverse(coll_list_t *list) {
    if (list->len == 0 || list->len == 1) {
        return;
    }
    node_t *cur = list->head->next, *next;
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

void coll_list_clear(coll_list_t *list) {
    node_t *cur = list->head->next;
    while (cur != list->head) {
        node_t *next = cur->next;
        coll_list_remove_node(list, cur);
        cur = next;
    }
}

void coll_list_free(coll_list_t *list) {
    coll_list_clear(list);
    free(list->head);
}
