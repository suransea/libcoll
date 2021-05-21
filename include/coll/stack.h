//
// Created by sea on 2019/11/28.
//

#ifndef LIBCOLL_STACK_H
#define LIBCOLL_STACK_H

#include <stdbool.h>
#include <stddef.h>

#include "coll/vector.h"

typedef struct coll_vector coll_stack_t;

void coll_stack_init(coll_stack_t *stack, size_t cap);

void coll_stack_push(coll_stack_t *stack, void *data);

void *coll_stack_pop(coll_stack_t *stack);

void *coll_stack_peek(coll_stack_t *stack);

size_t coll_stack_size(coll_stack_t *stack);

bool coll_stack_empty(coll_stack_t *stack);

void coll_stack_foreach(coll_stack_t *stack, void (*visit)(void *));

void coll_stack_clear(coll_stack_t *stack);

void coll_stack_free(coll_stack_t *stack);

#endif  //LIBCOLL_STACK_H
