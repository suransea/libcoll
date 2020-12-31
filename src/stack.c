//
// Created by sea on 2019/11/28.
//

#include "coll/stack.h"

#include "coll/vector.h"

Stack *stack_new(size_t cap) {
    return vector_new(cap);
}

void stack_push(Stack *stack, void *data) {
    vector_append(stack, data);
}

void *stack_pop(Stack *stack) {
    return vector_remove_last(stack);
}

void *stack_peek(Stack *stack) {
    return vector_last(stack);
}

size_t stack_size(Stack *stack) {
    return vector_size(stack);
}

bool stack_empty(Stack *stack) {
    return vector_empty(stack);
}

void stack_foreach(Stack *stack, void (*visit)(void *)) {
    vector_foreach(stack, visit);
}

void stack_clear(Stack *stack) {
    vector_clear(stack);
}

void stack_free(Stack *stack) {
    vector_free(stack);
}
