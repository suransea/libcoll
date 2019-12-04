//
// Created by sea on 2019/11/29.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/list.h"
#include "../src/dict.h"
#include "../src/queue.h"
#include "../src/ring.h"
#include "../src/map.h"
#include "../src/set.h"

void print_str(void *data) {
    printf("%s ", (char *) data);
}

bool equal_1d(void *data) {
    return strcmp(data, "1d") == 0;
}

void print_list(List *list) {
    printf("\n\nlen: %u\n", list_size(list));
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
    for (int i = 0; i < list_size(list); ++i) {
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
    dict_insert(dict, "name", "Alice");
    dict_insert(dict, "age", "10");
    dict_insert(dict, "age", "11");
    dict_insert(dict, "a", "d");
    dict_insert(dict, "b", "e");
    dict_insert(dict, "c", "f");
    print_dict(dict);
    print_str(dict_value_of(dict, "name"));
    print_str(dict_value_of(dict, "not_exist"));
    dict_remove(dict, "age");
    print_dict(dict);
    dict_free(dict);
}

void test_ring() {
    Ring *ring = ring_new(5);
    ring->data = "a";
    ring_insert(ring, "b");
    printf(" %u ", ring_size(ring));
    ring_foreach(ring_move(ring, 0), print_str);
    ring = ring_remove(ring, "a");
    ring_foreach(ring_move(ring, 0), print_str);
    ring_free(ring);
}

void print_map(Map *map) {
    printf("\nempty: %d, size: %u\n", map_empty(map), map_size(map));
    map_foreach(map, print_kv);
}

void test_map() {
    Map *map = map_new_custom(cmp_str);
    print_map(map);
    map_insert(map, "name", "Alice");
    map_insert(map, "age", "10");
    map_insert(map, "age", "11");
    map_insert(map, "a", "d");
    map_insert(map, "b", "e");
    map_insert(map, "c", "f");
    print_map(map);
    print_str(map_value_of(map, "name"));
    print_str(map_value_of(map, "not_exist"));
    map_remove(map, "age");
    print_map(map);
    map_clear(map);
    print_map(map);
    map_free(map);
}

void test_set() {
    Set *set = set_new();
    set_add(set, "a");
    set_add(set, "a");
    set_add(set, "a");
    set_add(set, "a");
    set_add(set, "b");
    set_foreach(set, print_str);
    set_free(set);
}

int main() {
    //test_list();
    //test_dict();
    test_map();
    //test_set();
    return 0;
}
