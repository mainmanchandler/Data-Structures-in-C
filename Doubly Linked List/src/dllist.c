/*
 -------------------------------------
 File:    dllist.c
 file description
 doubly linked list
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-15
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"

NODE* new_node(char data) {
	NODE *new = (NODE*) malloc(sizeof(NODE));
	new->value = data;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

/**
 * Prints the double linked list in-order
 * @param np, the start of the list
 */
void display_forward(NODE *np) {
	NODE *temp_printer = np;

	while (temp_printer != NULL) {
		printf("%c ", temp_printer->value);
		temp_printer = temp_printer->next;
	}

}

/**
 * Prints the double linked list backwards
 * @param np, the end of the list
 */
void display_backward(NODE *np) {
	NODE *temp_printer = np;
	while (temp_printer != NULL) {
		printf("%c ", temp_printer->value);
		temp_printer = temp_printer->prev;
	}
}

/**
 * inserts new node at the front of the list
 * @param start Pointer to the first node of double linked list.
 * @param endp Pointer to the last node in the list
 * @param new_np is Pointer to the new node to be pushed
 */
void insert_start(NODE **startp, NODE **endp, NODE *new_np) {
	//inserts node at the beginning of the linked list
	//by default main will insert 1-9 inserting at the start
	//9,8,7,6,5,4,3,2,1,0

	//if the list is empty, set both to new node:
	if (*startp == NULL && *endp == NULL) {
		*startp = new_np;
		*endp = new_np;

	} else { //otherwise put new node at beginning, push the rest to the right
		(*startp)->prev = new_np; //new start is new_np
		new_np->next = *startp; //pushes old start node to the right
		*startp = new_np; //make new_np the new start node
	}
}

/**
 * inserts new node at the back of the list
 * @param start Pointer to the first node of double linked list.
 * @param endp Pointer to the last node in the list
 * @param new_np is Pointer to the new node to be plopped
 */
void insert_end(NODE **startp, NODE **endp, NODE *new_np) {
	//inserts node at the beginning of the linked list
	//by default main will insert a-j inserting at the start
	//a b c d e f g h i j

	//if the list is empty, set both to new node:
	if (*startp == NULL && *endp == NULL) {
		*startp = new_np;
		*endp = new_np;

	} else { //otherwise put new node at beginning, push the rest to the right
		(*endp)->next = new_np; //new start is new_np
		new_np->prev = *endp; //pushes old start node to the right
		*endp = new_np; //make new_np the new start node
	}
}

/**
 * deletes the first node in the list
 * @param start Pointer to the first node of double linked list.
 * @param endp Pointer to the last node in the list
 */
void delete_start(NODE **startp, NODE **endp) {

	if (*startp != NULL && *endp != NULL) {
		NODE *temp_ptr = *startp;
		//free(startp); //feck ur memory leak thats what
		*startp = temp_ptr->next;
		(*startp)->prev = NULL;
	}
	return;
}

/**
 * deletes the end node in the list
 * @param start Pointer to the first node of double linked list.
 * @param endp Pointer to the last node in the list
 */
void delete_end(NODE **startp, NODE **endp) {

	if (*startp != NULL && *endp != NULL) {
		NODE *temp_ptr = *endp;
		//free(endp); //why tf you break my program, bruh you finna have a memory leak
		*endp = temp_ptr->prev;
		(*endp)->next = NULL;
	}
	return;
}

/**
 * deletes the whole list
 * @param start Pointer to the first node of double linked list.
 * @param endp Pointer to the last node in the list
 */
void clean(NODE **startp, NODE **endp) {
	NODE *currentp = *startp;
	NODE *prev = NULL;

	//delete every node in the list
	while (currentp != NULL) {
		prev = currentp;
		currentp = currentp->next;
		free(prev);
	}

	//reset start and end pointers
	*startp = NULL;
	*endp = NULL;

	return;
}
