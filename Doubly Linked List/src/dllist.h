/*
 -------------------------------------
 File:    dllist.h
 file description
 header file for double linked list
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-15
 -------------------------------------
 */

#ifndef DLLIST_H_
#define DLLIST_H_

typedef struct node {
	char value;
	struct node *prev; //previous node
	struct node *next; //next node
} NODE;

/*
 * This creates a new node using malloc().
 */
NODE* new_node(char data);

/*
 * This displays char data from start to end.
 */
void display_forward(NODE *start);

/*
 * This displays char data from end to start.
 */
void display_backward(NODE *end);

/*
 * This inserts a new node at the beginning the of doubly linked list.
 */
void insert_start(NODE **startp, NODE **endp, NODE *new_np);

/*
 * This inserts a new node at the end of the doubly linked list.
 */
void insert_end(NODE **startp, NODE **endp, NODE *new_np);

/*
 * This deletes the first node of the doubly linked list.
 */
void delete_start(NODE **startp, NODE **endp);

/*
 * This deletes the last node of the doubly linked list.
 */
void delete_end(NODE **startp, NODE **endp);

/*
 * This cleans the doubly linked list.
 */
void clean(NODE **startp, NODE **endp);

#endif /* DLLIST_H_ */
