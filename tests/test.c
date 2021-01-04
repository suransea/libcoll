//
// Created by sea on 2019/11/29.
//

#include "test.h"

#include <stdio.h>
#include <string.h>

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

void print_str(void *data) {
    printf("%s ", (char *) data);
}

bool equal_s(void *data) {
    return strcmp(data, "s") == 0;
}

void print_list(coll_list_t *list) {
    printf("\nlen: %zu\n", coll_list_size(list));
    coll_list_foreach(list, print_str);
    printf("\n");
}

test_func(list)
    coll_list_t *list = coll_list_new();
    coll_list_insert_sorted(list, "a", coll_cmp_str);
    coll_list_insert_sorted(list, "b", coll_cmp_str);
    coll_list_insert_sorted(list, "r", coll_cmp_str);
    coll_list_insert_sorted(list, "w", coll_cmp_str);
    coll_list_insert_sorted(list, "s", coll_cmp_str);
    coll_list_insert_sorted(list, "k", coll_cmp_str);
    coll_list_insert_sorted(list, "s", coll_cmp_str);
    coll_list_insert_sorted(list, "s", coll_cmp_str);
    print_list(list);

    assert_str_eq("r", coll_list_at(list, 3));
    assert_str_eq("a", coll_list_first(list));
    assert_str_eq("w", coll_list_last(list));

    assert_str_eq("a", coll_list_remove_first(list));
    print_list(list);

    assert_str_eq("w", coll_list_remove_last(list));
    print_list(list);

    assert_str_eq("k", coll_list_remove_at(list, 1));
    print_list(list);

    assert_eq(NULL, coll_list_remove(list, "a"));
    print_list(list);

    coll_list_insert_after(list, "k", "b");
    print_list(list);

    coll_list_insert_before(list, "g", "k");
    print_list(list);

    coll_list_insert_at(list, "f", 2);
    print_list(list);

    printf("remove:%s ", coll_list_remove_if(list, equal_s));
    print_list(list);

    printf("count:%zu ", coll_list_remove_all(list, "b"));
    print_list(list);

    printf("index:%zu ", coll_list_find(list, equal_s));
    printf("index:%zu ", coll_list_index_of(list, "g"));

    coll_list_reverse(list);
    print_list(list);

    printf("empty:%d ", coll_list_empty(list));
    coll_list_clear(list);
    printf("empty:%d ", coll_list_empty(list));

    coll_list_free(list);
test_func_end

void print_kv(void *k, void *v) {
    printf("\n%s: %s\n", k, v);
}

void print_hmap(coll_hmap_t *hmap) {
    printf("\nempty: %d, size: %zu\n", coll_hmap_empty(hmap), coll_hmap_size(hmap));
    coll_hmap_foreach(hmap, print_kv);
}

test_func(hmap)
    coll_hmap_t *map = coll_hmap_new_custom(0, coll_hash_str, coll_equal_str);
    print_hmap(map);
    coll_hmap_insert(map, "name", "Alice");
    coll_hmap_insert(map, "age", "10");
    coll_hmap_insert(map, "age", "11");
    coll_hmap_insert(map, "a", "d");
    coll_hmap_insert(map, "b", "e");
    coll_hmap_insert(map, "c", "f");
    print_hmap(map);
    assert_str_eq("Alice", coll_hmap_value_of(map, "name"));
    assert_eq(NULL, coll_hmap_value_of(map, "not_exist"));
    coll_hmap_remove(map, "age");
    print_hmap(map);
    coll_hmap_free(map);
test_func_end

void print_tmap(coll_tmap_t *map) {
    printf("\nempty: %d, size: %zu\n", coll_tmap_empty(map), coll_tmap_size(map));
    coll_tmap_foreach(map, print_kv);
}

test_func(tmap)
    coll_tmap_t *map = coll_tmap_new_custom(coll_cmp_str);
    print_tmap(map);
    coll_tmap_insert(map, "name", "Alice");
    coll_tmap_insert(map, "age", "10");
    coll_tmap_insert(map, "age", "11");
    coll_tmap_insert(map, "a", "d");
    coll_tmap_insert(map, "b", "e");
    coll_tmap_insert(map, "c", "f");
    print_tmap(map);
    assert_str_eq("Alice", coll_tmap_value_of(map, "name"));
    assert_eq(NULL, coll_tmap_value_of(map, "not_exist"));
    coll_tmap_remove(map, "age");
    print_tmap(map);
    coll_tmap_clear(map);
    print_tmap(map);
    coll_tmap_free(map);
test_func_end

test_func(tset)
    coll_tset_t *set = coll_tset_new();
    coll_tset_insert(set, "a");
    coll_tset_insert(set, "a");
    coll_tset_insert(set, "a");
    coll_tset_insert(set, "a");
    coll_tset_insert(set, "b");
    coll_tset_foreach(set, print_str);
    coll_tset_free(set);
test_func_end

test_func(heap)
    coll_heap_t *heap = coll_heap_new(coll_cmp_str);
    coll_heap_push(heap, "s");
    coll_heap_push(heap, "c");
    coll_heap_push(heap, "a");
    coll_heap_push(heap, "r");
    coll_heap_push(heap, "f");
    coll_heap_push(heap, "c");

    while (!coll_heap_empty(heap)) {
        printf("%s ", coll_heap_pop(heap));
    }
    coll_heap_free(heap);
test_func_end

test_func(vector)
    coll_vector_t *vector = coll_vector_new(0);
    coll_vector_prepend(vector, "1");
    coll_vector_prepend(vector, "f");
    coll_vector_prepend(vector, "q");
    coll_vector_prepend(vector, "v");
    coll_vector_prepend(vector, "t");
    coll_vector_prepend(vector, "s");
    coll_vector_append(vector, "a");
    coll_vector_insert_at(vector, "g", 3);
    coll_vector_insert_after(vector, "h", "g");
    coll_vector_insert_before(vector, "i", "g");
    coll_vector_remove_first(vector);
    coll_vector_foreach(vector, print_str);
    printf("\n");
test_func_end

test_func(seq)
    coll_seq_t *seq = coll_seq_new();
    coll_seq_prepend(seq, "a");
    coll_seq_prepend(seq, "b");
    coll_seq_prepend(seq, "c");
    coll_seq_prepend(seq, "d");
    coll_seq_prepend(seq, "e");
    coll_seq_prepend(seq, "f");
    coll_seq_reverse(seq);
    coll_seq_foreach(seq, print_str);
test_func_end

test_func(deque)
    coll_deque_t *deque = coll_deque_new(1);
    coll_deque_append(deque, "a");
    coll_deque_prepend(deque, "b");
    coll_deque_insert_at(deque, "c", 0);
    coll_deque_insert_at(deque, "d", 0);
    coll_deque_insert_at(deque, "e", 0);
    coll_deque_insert_after(deque, "g", "c");
    coll_deque_insert_before(deque, "f", "g");
    coll_deque_remove_at(deque, 5);
    coll_deque_foreach(deque, print_str);
test_func_end

int main() {
    invoke_test(test_list, test_vector, test_seq, test_deque,
                test_hmap, test_tmap,
                test_tset, test_heap);
    return 0;
}
