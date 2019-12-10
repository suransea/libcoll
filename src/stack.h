//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_STACK_H
#define LIBCOLL_STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _stack Stack;

Stack *stack_new();

void stack_push(Stack *stack, void *data);

void *stack_pop(Stack *stack);

void *stack_peek(Stack *stack);

size_t stack_size(Stack *stack);

bool stack_empty(Stack *stack);

void stack_foreach(Stack *stack, void(*visit)(void *));

void stack_clear(Stack *stack);

void stack_free(Stack *stack);

#endif //LIBCOLL_STACK_H
