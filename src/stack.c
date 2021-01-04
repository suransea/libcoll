//
// Created by sea on 2019/11/28.
//

#include "coll/stack.h"

#include "coll/vector.h"

coll_stack_t *coll_stack_new(size_t cap) {
    return coll_vector_new(cap);
}

void coll_stack_push(coll_stack_t *stack, void *data) {
    coll_vector_append(stack, data);
}

void *coll_stack_pop(coll_stack_t *stack) {
    return coll_vector_remove_last(stack);
}

void *coll_stack_peek(coll_stack_t *stack) {
    return coll_vector_last(stack);
}

size_t coll_stack_size(coll_stack_t *stack) {
    return coll_vector_size(stack);
}

bool coll_stack_empty(coll_stack_t *stack) {
    return coll_vector_empty(stack);
}

void coll_stack_foreach(coll_stack_t *stack, void (*visit)(void *)) {
    coll_vector_foreach(stack, visit);
}

void coll_stack_clear(coll_stack_t *stack) {
    coll_vector_clear(stack);
}

void coll_stack_free(coll_stack_t *stack) {
    coll_vector_free(stack);
}
