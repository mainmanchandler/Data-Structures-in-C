/*
 -------------------------------------
 File:    stack.c
 Stack data structure
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-01
 -------------------------------------
 */
#include <stdio.h>
#include "stack.h"

void push(STACK *sp, NODE *np) {

	//if the stack isnt empty then make np new top
	if (sp->top != NULL) {
		np->next = sp->top;
		sp->top = np;
	} else
		//first node
		sp->top = np;

	return;
}

NODE* pop(STACK *sp) {

	NODE *popped = NULL;

	//pop top off if it exists
	if (sp->top != NULL) {
		popped = sp->top;
		sp->top = sp->top->next;
	}

	return popped;
}

void clean_stack(STACK *sp) {
// your implementation,  use clean() function in common.h

//if the stack isnt empty:
	if (sp->top != NULL) {
		//go to each node in the queue
		//clean node using the common clean method
		while (sp->top != NULL) {
			clean(&sp->top);
		}
	}

	return;

}
