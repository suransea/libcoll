//
// Created by sea on 2019/11/29.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../src/list.h"
#include "../src/dict.h"
#include "../src/queue.h"
#include "../src/map.h"
#include "../src/set.h"
#include "../src/heap.h"
#include "../src/vector.h"
#include "../src/deque.h"

void print_str(void *data) {
    printf("%s ", (char *) data);
}

void print_ptr(void *ptr) {
    printf("%u ", (unsigned) ptr);
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
    print_str(list_first(list));
    print_str(list_last(list));
    for (int i = 0; i < list_size(list); ++i) {
        print_str(list_at(list, i));
    }

    print_str(list_remove_first(list));
    print_list(list);

    print_str(list_remove_last(list));
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

    printf("remove:%s ", list_remove_if(list, equal_1d));
    print_list(list);

    printf("count:%u ", list_remove_all(list, "b"));
    print_list(list);

    printf("index:%d ", list_find(list, equal_1d));
    printf("index:%d ", list_index_of(list, "g"));

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
    set_insert(set, "a");
    set_insert(set, "a");
    set_insert(set, "a");
    set_insert(set, "a");
    set_insert(set, "b");
    set_foreach(set, print_str);
    set_free(set);
}

void test_heap() {
    Heap *heap = heap_new(cmp_str);
    heap_push(heap, "s");
    heap_push(heap, "c");
    heap_push(heap, "a");
    heap_push(heap, "r");
    heap_push(heap, "f");
    heap_push(heap, "c");

    while (!heap_empty(heap)) {
        printf("%s ", heap_pop(heap));
    }
    heap_free(heap);
}

void test_vector() {
    Vector *vector = vector_new(0);
    vector_prepend(vector, "1");
    vector_prepend(vector, "f");
    vector_prepend(vector, "q");
    vector_prepend(vector, "v");
    vector_prepend(vector, "t");
    vector_prepend(vector, "s");
    vector_append(vector, "a");
    vector_insert_at(vector, "g", 3);
    vector_insert_after(vector, "afg", "g");
    vector_insert_before(vector, "bfg", "g");
    vector_remove_first(vector);
    vector_foreach(vector, print_str);
    printf("\n");
}

void test_seq() {
    Seq *seq = seq_new();
    seq_prepend(seq, "a");
    seq_prepend(seq, "b");
    seq_prepend(seq, "c");
    seq_prepend(seq, "d");
    seq_prepend(seq, "e");
    seq_prepend(seq, "f");
    seq_reverse(seq);
    seq_foreach(seq, print_str);
}

void test_deque() {
    Deque *deque = deque_new(1);
    deque_append(deque, "a");
    deque_prepend(deque, "b");
    deque_insert_at(deque, "c", 0);
    deque_insert_at(deque, "d", 0);
    deque_insert_at(deque, "e", 0);
    deque_insert_after(deque, "g", "c");
    deque_insert_before(deque, "f", "g");
    deque_remove_at(deque, 5);
    deque_foreach(deque, print_str);
}

int main() {
    //test_list();
    //test_dict();
    //test_map();
    //test_set();
    //test_heap();
    //test_vector();
    //test_seq();
    test_deque();
    return 0;
}
