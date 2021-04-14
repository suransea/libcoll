//
// Created by sea on 2019/11/29.
//

#include "test.h"

#include <stdio.h>
#include <string.h>

#include "coll.h"

void print_str(void *data) {
    printf("%s, ", (char *) data);
}

bool equal_a(void *data) {
    return strcmp(data, "a") == 0;
}

void print_kv(void *k, void *v) {
    printf("%s: %s, ", k, v);
}

test_func(array)
    coll_array_t *array = coll_array_new(3);
    coll_array_assign(array, 0, "a");
    coll_array_assign(array, 1, "b");
    assert_eq_str("a", coll_array_at(array, 0));
    coll_array_assign(array, 0, "c");
    assert_eq_str("c", coll_array_at(array, 0));
    assert_eq_str("c", coll_array_first(array));
    assert_eq(NULL, coll_array_last(array));
    assert_eq(3, coll_array_size(array));
    assert_eq(0, coll_array_index_of(array, "c"));
    assert_eq(3, coll_array_index_of(array, "d"));
    coll_array_foreach(array, print_str);
    coll_array_free(array);
test_func_end

test_func(deque)
    coll_deque_t *deque = coll_deque_new(1);
    assert(coll_deque_empty(deque));
    coll_deque_append(deque, "a");
    coll_deque_prepend(deque, "b");
    assert_eq_str("b", coll_deque_at(deque, 0));
    assert_eq_str("a", coll_deque_at(deque, 1));
    assert_eq_str("b", coll_deque_first(deque));
    assert_eq_str("a", coll_deque_last(deque));
    coll_deque_insert_at(deque, "c", 0);
    coll_deque_insert_at(deque, "d", 0);
    coll_deque_insert_at(deque, "e", 0);
    assert_eq_str("e", coll_deque_first(deque));
    coll_deque_insert_after(deque, "g", "c");
    assert_eq_str("g", coll_deque_at(deque, 3));
    coll_deque_insert_before(deque, "f", "g");
    assert_eq_str("f", coll_deque_at(deque, 3));
    assert_eq_str("b", coll_deque_remove_at(deque, 5));
    assert_eq(NULL, coll_deque_at(deque, 6));
    assert_eq(6, coll_deque_size(deque));
    coll_deque_foreach(deque, print_str);
    coll_deque_free(deque);
test_func_end

test_func(heap)
    coll_heap_t *heap = coll_heap_new(coll_cmp_str);
    assert(coll_heap_empty(heap));
    coll_heap_push(heap, "s");
    coll_heap_push(heap, "c");
    coll_heap_push(heap, "a");
    coll_heap_push(heap, "r");
    coll_heap_push(heap, "f");
    coll_heap_push(heap, "c");
    assert(!coll_heap_empty(heap));
    coll_heap_foreach(heap, print_str);
    assert_eq_str("s", coll_heap_top(heap));
    assert_eq_str("s", coll_heap_pop(heap));
    assert_eq_str("r", coll_heap_pop(heap));
    assert_eq_str("f", coll_heap_pop(heap));
    assert_eq_str("c", coll_heap_pop(heap));
    assert_eq_str("c", coll_heap_pop(heap));
    assert_eq_str("a", coll_heap_pop(heap));
    assert(coll_heap_empty(heap));
    coll_heap_free(heap);
test_func_end

test_func(hmap)
    coll_hmap_t *map = coll_hmap_new_custom(0, coll_hash_str, coll_equal_str);
    assert(coll_hmap_empty(map));
    coll_hmap_insert(map, "name", "Alice");
    coll_hmap_insert(map, "age", "10");
    coll_hmap_insert(map, "age", "11");
    coll_hmap_insert(map, "a", "d");
    coll_hmap_insert(map, "b", "e");
    coll_hmap_insert(map, "c", "f");
    assert_eq_str("Alice", coll_hmap_value_of(map, "name"));
    assert_eq_str("11", coll_hmap_value_of(map, "age"));
    assert_eq(NULL, coll_hmap_value_of(map, "not_exist"));
    assert(coll_hmap_contains_key(map, "name"));
    assert(!coll_hmap_contains_key(map, "not_exist"));
    assert(coll_hmap_contains_value(map, "Alice"));
    assert(!coll_hmap_contains_value(map, "not_exist"));
    assert_eq_str("11", coll_hmap_remove(map, "age"));
    assert(!coll_hmap_contains_key(map, "age"));
    assert(!coll_hmap_contains_value(map, "11"));
    assert_eq(NULL, coll_hmap_value_of(map, "age"));
    assert_eq(4, coll_hmap_size(map));
    coll_hmap_foreach(map, print_kv);
    coll_hmap_free(map);
test_func_end

test_func(hset)
    coll_hset_t *set = coll_hset_new(8);
    assert(coll_hset_empty(set));
    assert(coll_hset_insert(set, "a"));
    assert(!coll_hset_insert(set, "a"));
    coll_hset_insert(set, "b");
    assert_eq(2, coll_hset_size(set));
    assert(coll_hset_contains(set, "a"));
    assert(!coll_hset_contains(set, "not_exist"));
    assert(coll_hset_remove(set, "a"));
    assert(!coll_hset_remove(set, "not_exist"));
    coll_hset_foreach(set, print_str);
    coll_hset_free(set);
test_func_end

test_func(list)
    coll_list_t *list = coll_list_new();
    assert(coll_list_empty(list));
    coll_list_insert_sorted(list, "a", coll_cmp_str);
    coll_list_insert_sorted(list, "b", coll_cmp_str);
    coll_list_insert_sorted(list, "r", coll_cmp_str);
    coll_list_insert_sorted(list, "w", coll_cmp_str);
    coll_list_insert_sorted(list, "s", coll_cmp_str);
    coll_list_insert_sorted(list, "k", coll_cmp_str);
    coll_list_insert_sorted(list, "s", coll_cmp_str);
    coll_list_insert_sorted(list, "s", coll_cmp_str);
    coll_list_insert_sorted(list, "a", coll_cmp_str);
    assert_eq_str("r", coll_list_at(list, 4));
    assert_eq_str("a", coll_list_first(list));
    assert_eq_str("w", coll_list_last(list));
    assert_eq_str("a", coll_list_remove_first(list));
    assert_eq_str("w", coll_list_remove_last(list));
    assert_eq_str("k", coll_list_remove_at(list, 2));
    assert_eq(NULL, coll_list_remove(list, "k"));
    coll_list_insert_after(list, "k", "b");
    coll_list_insert_before(list, "g", "k");
    coll_list_insert_at(list, "f", 2);
    assert_eq_str("a", coll_list_remove_if(list, equal_a));
    assert_eq(NULL, coll_list_remove_if(list, equal_a));
    assert_eq(1, coll_list_remove_all(list, "b"));
    assert_eq(7, coll_list_size(list));
    assert_eq(7, coll_list_find(list, equal_a));
    assert_eq(1, coll_list_index_of(list, "g"));
    coll_list_reverse(list);
    assert_eq_str("s", coll_list_first(list));
    assert_eq_str("f", coll_list_last(list));
    assert(!coll_list_empty(list));
    coll_list_foreach(list, print_str);
    coll_list_clear(list);
    assert(coll_list_empty(list));
    coll_list_free(list);
test_func_end

test_func(queue)
    coll_queue_t *queue = coll_queue_new(8);
    assert(coll_queue_empty(queue));
    coll_queue_push(queue, "a");
    coll_queue_push(queue, "b");
    coll_queue_push(queue, "c");
    assert_eq_str("a", coll_queue_front(queue));
    assert_eq_str("c", coll_queue_back(queue));
    assert_eq(3, coll_queue_size(queue));
    coll_queue_foreach(queue, print_str);
    assert_eq_str("a", coll_queue_pop(queue));
    assert_eq_str("b", coll_queue_pop(queue));
    assert_eq_str("c", coll_queue_pop(queue));
    assert(coll_queue_empty(queue));
    coll_queue_free(queue);
test_func_end

test_func(seq)
    coll_seq_t *seq = coll_seq_new();
    assert(coll_seq_empty(seq));
    coll_seq_prepend(seq, "a");
    assert_eq_str("a", coll_seq_first(seq));
    coll_seq_prepend(seq, "b");
    coll_seq_prepend(seq, "c");
    coll_seq_prepend(seq, "d");
    coll_seq_prepend(seq, "e");
    coll_seq_prepend(seq, "f");
    assert_eq(6, coll_seq_size(seq));
    assert_eq_str("f", coll_seq_first(seq));
    assert_eq_str("a", coll_seq_last(seq));
    coll_seq_reverse(seq);
    assert_eq_str("a", coll_seq_first(seq));
    assert_eq_str("f", coll_seq_last(seq));
    assert_eq_str("c", coll_seq_at(seq, 2));
    assert_eq_str("c", coll_seq_remove_at(seq, 2));
    assert_eq_str("d", coll_seq_at(seq, 2));
    coll_seq_foreach(seq, print_str);
    coll_seq_free(seq);
test_func_end

test_func(stack)
    coll_stack_t *stack = coll_stack_new(8);
    assert(coll_stack_empty(stack));
    coll_stack_push(stack, "a");
    coll_stack_push(stack, "b");
    coll_stack_push(stack, "c");
    assert_eq(3, coll_stack_size(stack));
    coll_stack_foreach(stack, print_str);
    assert_eq_str("c", coll_stack_peek(stack));
    assert_eq_str("c", coll_stack_pop(stack));
    assert_eq_str("b", coll_stack_pop(stack));
    assert_eq_str("a", coll_stack_pop(stack));
    assert(coll_stack_empty(stack));
    coll_stack_free(stack);
test_func_end

test_func(tmap)
    coll_tmap_t *map = coll_tmap_new_custom(coll_cmp_str);
    assert(coll_tmap_empty(map));
    coll_tmap_insert(map, "name", "Alice");
    coll_tmap_insert(map, "age", "10");
    coll_tmap_insert(map, "age", "11");
    coll_tmap_insert(map, "a", "d");
    coll_tmap_insert(map, "b", "e");
    coll_tmap_insert(map, "c", "f");
    assert_eq_str("Alice", coll_tmap_value_of(map, "name"));
    assert_eq_str("11", coll_tmap_value_of(map, "age"));
    assert_eq(NULL, coll_tmap_value_of(map, "not_exist"));
    assert(coll_tmap_contains_key(map, "name"));
    assert(!coll_tmap_contains_key(map, "not_exist"));
    assert(coll_tmap_contains_value(map, "Alice"));
    assert(!coll_tmap_contains_value(map, "not_exist"));
    assert_eq_str("11", coll_tmap_remove(map, "age"));
    assert(!coll_tmap_contains_key(map, "age"));
    assert(!coll_tmap_contains_value(map, "11"));
    assert_eq(NULL, coll_tmap_value_of(map, "age"));
    assert_eq(4, coll_tmap_size(map));
    coll_tmap_foreach(map, print_kv);
    coll_tmap_free(map);
test_func_end

test_func(tset)
    coll_tset_t *set = coll_tset_new();
    assert(coll_tset_empty(set));
    assert(coll_tset_insert(set, "a"));
    assert(!coll_tset_insert(set, "a"));
    coll_tset_insert(set, "b");
    assert_eq(2, coll_tset_size(set));
    assert(coll_tset_contains(set, "a"));
    assert(!coll_tset_contains(set, "not_exist"));
    assert(coll_tset_remove(set, "a"));
    assert(!coll_tset_remove(set, "not_exist"));
    coll_tset_foreach(set, print_str);
    coll_tset_free(set);
test_func_end

test_func(tuple)
    coll_pair_t pair = {"a", "b"};
    assert_eq_str("a", pair._0);
    assert_eq_str("b", pair._1);
    coll_triple_t triple = {"a"};
    assert_eq_str("a", triple._0);
    assert_eq(NULL, triple._1);
    assert_eq(NULL, triple._2);
    coll_tuple4_t tuple4 = {};
    coll_tuple5_t tuple5 = {};
    assert_eq(NULL, tuple4._0);
    assert_eq(NULL, tuple5._0);
test_func_end

test_func(vector)
    coll_vector_t *vector = coll_vector_new(1);
    assert(coll_vector_empty(vector));
    coll_vector_append(vector, "a");
    coll_vector_prepend(vector, "b");
    assert_eq_str("b", coll_vector_at(vector, 0));
    assert_eq_str("a", coll_vector_at(vector, 1));
    assert_eq_str("b", coll_vector_first(vector));
    assert_eq_str("a", coll_vector_last(vector));
    coll_vector_insert_at(vector, "c", 0);
    coll_vector_insert_at(vector, "d", 0);
    coll_vector_insert_at(vector, "e", 0);
    assert_eq_str("e", coll_vector_first(vector));
    coll_vector_insert_after(vector, "g", "c");
    assert_eq_str("g", coll_vector_at(vector, 3));
    coll_vector_insert_before(vector, "f", "g");
    assert_eq_str("f", coll_vector_at(vector, 3));
    assert_eq_str("b", coll_vector_remove_at(vector, 5));
    assert_eq(NULL, coll_vector_at(vector, 6));
    assert_eq(6, coll_vector_size(vector));
    coll_vector_foreach(vector, print_str);
    coll_vector_free(vector);
test_func_end

int main() {
    invoke_test(test_array, test_deque, test_heap, test_hmap,
                test_hset, test_list, test_queue, test_seq,
                test_stack, test_tmap, test_tset, test_tuple,
                test_vector);
    return 0;
}
