/*
 -------------------------------------
 File:    tree.c
 file description
 general binary tree methods
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-11
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* this computes and returns TPROPS value containing the number of nodes and height
 * of tree passed by root.
 */
TPROPS get_props(TNODE *root) {
	TPROPS tree_data = { 0 };
	tree_data.count = count_getter(root);   //call an aux recursive function to get the count of all of the nodes
	tree_data.height = height_getter(root); //call an aux recursive function to get the heigh of the tree
	return tree_data;
}

int height_getter(TNODE *rnode) {

	//left height and right height
	int left_h;
	int right_h;

	if (rnode == NULL)
		return 0;

	//recurse through the left and right to find the lowest point
	left_h = height_getter(rnode->left);
	right_h = height_getter(rnode->right);

	return (left_h > right_h ? left_h : right_h) + 1; //add 1 for root
}

int count_getter(TNODE *rnode) {

	int count = 1;

	//recurse and count all of the nodes in the list if the root is not null
	if (rnode) {
		if (rnode->left)
			count += count_getter(rnode->left);

		if (rnode->right)
			count += count_getter(rnode->right);

	} else
		return 0; //if the root is null then return 0

	return count;

}

/* this displays the node data of the tree by pre-order. */
void display_preorder(TNODE *root) {
	//displays in preorder: A B D E C F G
	if (root != NULL) {
		printf("%c ", root->data);
		display_preorder(root->left);
		display_preorder(root->right);
	}
}

/* this displays the node data of the tree by in-order. */
void display_inorder(TNODE *root) {
	//displays in inorder: D B E A F C G
	if (root != NULL) {
		display_inorder(root->left);
		printf("%c ", root->data);
		display_inorder(root->right);
	}
}

/* this displays the node data of the tree by post-order. */
void display_postorder(TNODE *root) {
	//displays in postorder: D E B F G C A
	if (root != NULL) {
		display_postorder(root->left);
		display_postorder(root->right);
		printf("%c ", root->data);
	}
}

/* this does the breadth-first search */
TNODE* iterative_bf_search(TNODE *root, int val) {

	QUEUE queue = { 0 };
	TNODE *r = NULL, *tp = NULL;

	if (root == NULL) //if the root is NULL then exit
		return r;

	enqueue(&queue, root);
	while (queue.front != NULL && r == NULL) {
		tp = dequeue(&queue); //fifo node from the front of the queue

		//printf("%c ", tp->data);

		if (tp->data == val)
			r = tp;

		//iterate through all of the children
		if (tp->left)
			enqueue(&queue, tp->left);
		if (tp->right)
			enqueue(&queue, tp->right);
	}

	clean_queue(&queue);

	return r;
}

/* this does the depth-first search */
TNODE* iterative_df_search(TNODE *root, int val) {

	STACK stack = { 0 };
	TNODE *r = NULL, *tp;

	if (root == NULL) //if the root is NULL then exit
		return r;

	push(&stack, root);

	//printf("\n");

	while (stack.top && r == NULL) {
		tp = peek(&stack); //get the node at the top if its there
		pop(&stack);	   //pop the node off of the top once its retrieved

		//printf("%c ", tp->data);

		if (tp->data == val) {
			r = tp;
		}

		//iterate through all of the children
		if (tp->left)
			push(&stack, tp->left);
		if (tp->right)
			push(&stack, tp->right);

	}

	clean_stack(&stack);
	return r;

}

/* basic functions */
TNODE* new_node(int value) {
	TNODE *np = (TNODE*) malloc(sizeof(TNODE));
	if (np == NULL)
		return NULL;
	np->data = value;
	np->left = NULL;
	np->right = NULL;
	return np;
}

void display_tree(TNODE *root, int prelen) {
	if (root) {
		int i;
		for (i = 0; i < prelen; i++)
			printf("%c", ' ');
		printf("%s", "|___");
		printf("%c\n", root->data);
		display_tree(root->right, prelen + 4);
		display_tree(root->left, prelen + 4);
	}
}

void clean_tree(TNODE **rootp) {
	TNODE *root = *rootp;
	if (root) {
		if (root->left)
			clean_tree(&root->left);
		if (root->right)
			clean_tree(&root->right);
		free(root);
	}
	*rootp = NULL;
}

// queue functions adapted and modified from a6
void enqueue(QUEUE *qp, void *data) {
	QNODE *p = (QNODE*) malloc(sizeof(QNODE));
	if (p == NULL)
		return;
	else {
		p->data = data;
		p->next = NULL;

		if (qp->front == NULL) {
			qp->front = p;
			qp->rear = p;
		} else {
			(qp->rear)->next = p;
			qp->rear = p;
		}
	}
}

void* dequeue(QUEUE *qp) {
	void *temp = NULL;
	if (qp->front) {
		QNODE *p = qp->front;
		temp = p->data;
		if (qp->front == qp->rear) {
			qp->front = NULL;
			qp->rear = NULL;
		} else {
			qp->front = p->next;
		}
		free(p);
		return temp;
	}
	return NULL;
}

void clean_queue(QUEUE *qp) {
	QNODE *temp, *p = qp->front;
	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
}

// stack functions adapted and modified from a6
void push(STACK *sp, void *data) {
	SNODE *p = (SNODE*) malloc(sizeof(SNODE));
	p->data = data;
	p->next = NULL;
	if (sp->top == NULL) {
		sp->top = p;
	} else {
		p->next = sp->top;
		sp->top = p;
	}
}

void pop(STACK *sp) {
	if (sp->top != NULL) {
		SNODE *p = sp->top;
		sp->top = p->next;
		free(p);
	}
}

void* peek(STACK *sp) {
	if (sp->top != NULL) {
		return sp->top->data;
	}
	return NULL;
}

void clean_stack(STACK *sp) {
	SNODE *temp, *p = sp->top;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	sp->top = NULL;
}
