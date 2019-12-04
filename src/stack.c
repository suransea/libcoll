//
// Created by sea on 2019/11/28.
//

#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct _stack {
  List *list;
};

Stack *stack_new() {
    Stack *stack = malloc(sizeof(Stack));
    stack->list = list_new();
    return stack;
}

void stack_push(Stack *stack, void *data) {
    list_prepend(stack->list, data);
}

void *stack_pop(Stack *stack) {
    if (list_size(stack->list) == 0) {
        return NULL;
    }
    void *data = list_front(stack->list);
    list_remove_front(stack->list);
    return data;
}

void *stack_peek(Stack *stack) {
    if (list_size(stack->list) == 0) {
        return NULL;
    }
    return list_front(stack->list);
}

size_t stack_size(Stack *stack) {
    return list_size(stack->list);
}

bool stack_empty(Stack *stack) {
    return list_empty(stack->list);
}

void stack_clear(Stack *stack) {
    list_clear(stack->list);
}

void stack_free(Stack *stack) {
    list_free(stack->list);
    free(stack);
}
