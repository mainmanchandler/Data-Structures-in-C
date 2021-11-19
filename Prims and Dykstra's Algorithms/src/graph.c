/*
 -------------------------------------
 File:    graph.c
 file description
 graph data structure implementation
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-04-09
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

GRAPH* new_graph(int order) {

	//create the new graph and init. its attributes
	GRAPH *graph = malloc(sizeof(new_graph));
	graph->order = order; //number of nodes
	graph->size = 0;
	graph->nodes = malloc(order * sizeof(GNODE*));

	//create all of the nodes in the graph and init. them to Null with nid being its index
	for (int i = 0; i < order; i++) {
		graph->nodes[i] = malloc(sizeof(GNODE));
		graph->nodes[i]->nid = i; //set graph node id to i
		graph->nodes[i]->neighbor = NULL; // init the neighbour in the linked list
	}

	return graph;
}

void add_edge(GRAPH *g, int from, int to, int weight) {

	//from is the start position, to is the last position

	ADJNODE *prev = NULL;
	ADJNODE *curr = g->nodes[from]->neighbor;

	//if curr is null to start then there is no 'from' node, so make the node at 'from'
	if (curr == NULL) {
		ADJNODE *new_adj = (ADJNODE*) malloc(sizeof(ADJNODE));
		new_adj->nid = to;
		new_adj->weight = weight;
		new_adj->next = NULL;

		g->nodes[from]->neighbor = new_adj;

	} else {

		//find where curr will equal NULL
		while (curr) {
			prev = curr;
			curr = curr->next;
		}

		//when curr is null that means there is an empty spot in the list, so make it a new node
		if (curr == NULL) {
			ADJNODE *new_adj = (ADJNODE*) malloc(sizeof(ADJNODE));
			new_adj->nid = to;
			new_adj->weight = weight;
			new_adj->next = NULL;

			prev->next = new_adj;
		}
	}

	g->size++;

	return;

}

void bf_traverse(GRAPH *g, int nid) {

	//if the graph doesnt exist then return
	if (g == NULL)
		return;

	//grab the number of nodes, and make an array of visited nodes
	int n = g->order;
	int visited[n];

	//set all of the nodes in visited to 0 (not visited)
	for (int i = 0; i < n; i++)
		visited[i] = 0;

	//traverse through the number of nodes breadth first (horizontal then down)
	QUEUE queue = { 0 };
	GNODE *gnp = NULL; 	 //gnode pointer
	ADJNODE *anp = NULL; //adjacent node pointer

	enqueue(&queue, g->nodes[nid]); //start and queue from nid position
	visited[nid] = 1;

	int i = 0;
	while (queue.front != NULL) {
		gnp = (GNODE*) dequeue(&queue);
		printf("%d ", gnp->nid);
		anp = gnp->neighbor;

		while (anp != NULL) {
			i = anp->nid; //grab the position

			//if the node hasnt been visited enqueue the node and make it visited
			if (visited[i] == 0) {
				visited[i] = 1;
				enqueue(&queue, g->nodes[i]);
			}

			anp = anp->next;

		}
	}

	clean_queue(&queue);

}

//use auxiliary stack data structure for the algorithm
void df_traverse(GRAPH *g, int nid) {
	//if the graph doesnt exist then return
	if (g == NULL)
		return;

	//grab the number of nodes, and make an array of visited nodes
	int n = g->order;
	int visited[n];

	//set all of the nodes in visited to 0 (not visited)
	for (int i = 0; i < n; i++)
		visited[i] = 0;

	//traverse through the number of nodes breadth first (down then horizontal)
	STACK stack = { 0 };
	GNODE *gnp = NULL; 	 //gnode pointer
	ADJNODE *anp = NULL; //adjacent node pointer

	push(&stack, g->nodes[nid]); //start and push from nid position
	visited[nid] = 1;

	int i = 0;
	while (stack.top != NULL) {
		gnp = (GNODE*) peek(&stack); //grab the node before popping it
		pop(&stack); 				// pop the node off of the stack
		printf("%d ", gnp->nid);
		anp = gnp->neighbor;

		while (anp) {
			i = anp->nid; //grab the position

			//if the node hasnt been visited push the node and make it visited
			if (visited[i] == 0) {
				visited[i] = 1;
				push(&stack, g->nodes[i]);
			}

			anp = anp->next;

		}
	}

	clean_stack(&stack);
}

int get_weight(GRAPH *g, int from, int to) {
	ADJNODE *p = g->nodes[from]->neighbor;
	int result = INFINITY;
	while (p) {
		if (p->nid == to) {
			result = p->weight;
			break;
		}
		p = p->next;
	}
	return result;
}

void clean_graph(GRAPH **gp) {
	int i;
	GRAPH *g = *gp;
	ADJNODE *temp, *ptr;
	for (i = 0; i < g->order; i++) {
		ptr = g->nodes[i]->neighbor;
		while (ptr != NULL) {
			temp = ptr;
			ptr = ptr->next;
			free(temp);
		}
		free(g->nodes[i]);
	}
	free(g->nodes);
	free(g);
	*gp = NULL;
}

void display_graph(GRAPH *g) {
	if (g == NULL)
		return;
	printf("order:%d\n", g->order);
	printf("size:%d\n", g->size);
	printf("from:(to weight)");
	int i;
	ADJNODE *ptr;
	for (i = 0; i < g->order; i++) {
		printf("\n%d:", g->nodes[i]->nid);
		ptr = g->nodes[i]->neighbor;
		while (ptr != NULL) {
			printf("(%d %d) ", ptr->nid, ptr->weight);
			ptr = ptr->next;
		}
	}
}

// queue functions adapted and modified from a7
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

// stack functions adapted and modified from a6q3
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
