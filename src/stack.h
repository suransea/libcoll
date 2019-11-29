//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_STACK_H
#define LIBCOLL_STACK_H

#include <stdbool.h>

typedef struct _stack Stack;

Stack *stack_new();

void stack_push(Stack *stack, void *data);

void *stack_pop(Stack *stack);

void *stack_peek(Stack *stack);

bool stack_empty(Stack *stack);

#endif //LIBCOLL_STACK_H
