/*
-------------------------------------
File:    stack.h
file description
header for stack data structure _init
-------------------------------------
Author:  Chandler Mayberry
Version  2021-03-01
-------------------------------------
 */

#ifndef STACK_H_
#define STACK_H_
#include "common.h"

typedef struct stack {
  NODE *top;
} STACK;

void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void clean_stack(STACK *sp);

#endif /* STACK_H_ */
