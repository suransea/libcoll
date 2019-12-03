//
// Created by sea on 2019/11/29.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/list.h"
#include "../src/dict.h"
#include "../src/queue.h"

void print_str(void *data) {
    printf("%s ", (char *) data);
}

int cmp_str(void *x, void *y) {
    return -strcmp(x, y);
}

bool equal_1d(void *data) {
    return strcmp(data, "1d") == 0;
}

void print_list(List *list) {
    printf("\n\nlen: %u\n", list_len(list));
    list_foreach(list, print_str);
    printf("\n\n");
}

void test_list() {
    List *list = list_new();
    list_insert_sorted(list, "a", cmp_str);
    list_insert_sorted(list, "b", cmp_str);
    list_insert_sorted(list, "rtfd", cmp_str);
    list_insert_sorted(list, "we", cmp_str);
    list_insert_sorted(list, "1d", cmp_str);
    list_insert_sorted(list, "kg", cmp_str);
    list_insert_sorted(list, "1d", cmp_str);
    list_insert_sorted(list, "1d", cmp_str);
    print_list(list);

    print_str(list_at(list, 3));
    print_str(list_front(list));
    print_str(list_back(list));
    for (int i = 0; i < list_len(list); ++i) {
        print_str(list_at(list, i));
    }

    print_str(list_remove_front(list));
    print_list(list);

    print_str(list_remove_back(list));
    print_list(list);

    print_str(list_remove_at(list, 1));
    print_list(list);

    print_str(list_remove(list, "a"));
    print_list(list);

    list_insert_after(list, "k", "b");
    print_list(list);

    list_insert_before(list, "g", "k");
    print_list(list);

    list_insert_at(list, "f", 2);
    print_list(list);

    printf("count:%u ", list_remove_if(list, equal_1d));
    print_list(list);

    printf("count:%u ", list_remove_all(list, "b"));
    print_list(list);

    printf("index:%d ", list_find(list, equal_1d));
    printf("index:%d ", list_index_of(list, "g"));

    list_sort(list, cmp_str);
    print_list(list);

    list_reverse(list);
    print_list(list);

    printf("empty:%d ", list_empty(list));
    list_clear(list);
    printf("empty:%d ", list_empty(list));

    list_free(list);
}

void print_kv(void *k, void *v) {
    printf("\n%s: %s\n", k, v);
}

void print_dict(Dict *dict) {
    printf("\nempty: %d, size: %u\n", dict_empty(dict), dict_size(dict));
    dict_foreach(dict, print_kv);
}

void test_dict() {
    Dict *dict = dict_new_custom(0, hash_str, equal_str);
    print_dict(dict);
    dict_add(dict, "name", "Alice");
    dict_add(dict, "age", "10");
    dict_add(dict, "age", "11");
    dict_add(dict, "a", "d");
    dict_add(dict, "b", "e");
    dict_add(dict, "c", "f");
    print_dict(dict);
    print_str(dict_value_of(dict, "name"));
    print_str(dict_value_of(dict, "not_exist"));
}

#define test test_dict();

int main() {
    test
    return 0;
}
