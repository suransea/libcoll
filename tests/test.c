//
// Created by sea on 2019/11/29.
//

#include "coll/array.h"
#include "coll/deque.h"
#include "coll/heap.h"
#include "coll/hmap.h"
#include "coll/hset.h"
#include "coll/list.h"
#include "coll/tmap.h"
#include "coll/tset.h"
#include "coll/tuple.h"
#include "coll/vector.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define test_func printf("\n\n-----\t%s\t-----\n", __func__);

void print_str(void *data) {
    printf("%s ", (char *) data);
}

void print_ptr(void *ptr) {
    printf("%u ", (unsigned) ptr);
}

bool equal_s(void *data) {
    return strcmp(data, "s") == 0;
}

void print_list(List *list) {
    printf("\n\nlen: %zu\n", list_size(list));
    list_foreach(list, print_str);
    printf("\n\n");
}

void test_list() {
    test_func
    List *list = list_new();
    list_insert_sorted(list, "a", cmp_str);
    list_insert_sorted(list, "b", cmp_str);
    list_insert_sorted(list, "r", cmp_str);
    list_insert_sorted(list, "w", cmp_str);
    list_insert_sorted(list, "s", cmp_str);
    list_insert_sorted(list, "k", cmp_str);
    list_insert_sorted(list, "s", cmp_str);
    list_insert_sorted(list, "s", cmp_str);
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

    printf("remove:%s ", list_remove_if(list, equal_s));
    print_list(list);

    printf("count:%zu ", list_remove_all(list, "b"));
    print_list(list);

    printf("index:%zu ", list_find(list, equal_s));
    printf("index:%zu ", list_index_of(list, "g"));

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

void print_hmap(HMap *hmap) {
    printf("\nempty: %d, size: %zu\n", hmap_empty(hmap), hmap_size(hmap));
    hmap_foreach(hmap, print_kv);
}

void test_hmap() {
    test_func
    HMap *map = hmap_new_custom(0, hash_str, equal_str);
    print_hmap(map);
    hmap_insert(map, "name", "Alice");
    hmap_insert(map, "age", "10");
    hmap_insert(map, "age", "11");
    hmap_insert(map, "a", "d");
    hmap_insert(map, "b", "e");
    hmap_insert(map, "c", "f");
    print_hmap(map);
    print_str(hmap_value_of(map, "name"));
    print_str(hmap_value_of(map, "not_exist"));
    hmap_remove(map, "age");
    print_hmap(map);
    hmap_free(map);
}

void print_tmap(TMap *map) {
    printf("\nempty: %d, size: %zu\n", tmap_empty(map), tmap_size(map));
    tmap_foreach(map, print_kv);
}

void test_tmap() {
    test_func
    TMap *map = tmap_new_custom(cmp_str);
    print_tmap(map);
    tmap_insert(map, "name", "Alice");
    tmap_insert(map, "age", "10");
    tmap_insert(map, "age", "11");
    tmap_insert(map, "a", "d");
    tmap_insert(map, "b", "e");
    tmap_insert(map, "c", "f");
    print_tmap(map);
    print_str(tmap_value_of(map, "name"));
    print_str(tmap_value_of(map, "not_exist"));
    tmap_remove(map, "age");
    print_tmap(map);
    tmap_clear(map);
    print_tmap(map);
    tmap_free(map);
}

void test_set() {
    test_func
    TSet *set = tset_new();
    tset_insert(set, "a");
    tset_insert(set, "a");
    tset_insert(set, "a");
    tset_insert(set, "a");
    tset_insert(set, "b");
    tset_foreach(set, print_str);
    tset_free(set);
}

void test_heap() {
    test_func
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
    test_func
    Vector *vector = vector_new(0);
    vector_prepend(vector, "1");
    vector_prepend(vector, "f");
    vector_prepend(vector, "q");
    vector_prepend(vector, "v");
    vector_prepend(vector, "t");
    vector_prepend(vector, "s");
    vector_append(vector, "a");
    vector_insert_at(vector, "g", 3);
    vector_insert_after(vector, "h", "g");
    vector_insert_before(vector, "i", "g");
    vector_remove_first(vector);
    vector_foreach(vector, print_str);
    printf("\n");
}

void test_seq() {
    test_func
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
    test_func
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
    test_list();
    test_hmap();
    test_tmap();
    test_set();
    test_heap();
    test_vector();
    test_seq();
    test_deque();
    return 0;
}
