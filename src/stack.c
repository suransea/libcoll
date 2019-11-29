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
    if (stack->list->len == 0) {
        return NULL;
    }
    void *data = list_front(stack->list)->data;
    list_remove(stack->list, data);
    return data;
}

void *stack_peek(Stack *stack) {
    if (stack->list->len == 0) {
        return NULL;
    }
    return list_front(stack->list)->data;
}

bool stack_empty(Stack *stack) {
    return stack->list == NULL;
}
