/*
 -------------------------------------
 File:    edgelist.c
 file description
 edgelist methods file with implementation
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-04-09
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"

EDGELIST* new_edgelist() {
	//create new edgelist and init. all of its attributes
	EDGELIST *p = malloc(sizeof(EDGELIST));
	p->size = 0;
	p->start = NULL;
	p->end = NULL;
	return p;
}

void add_edge_end(EDGELIST *g, int from, int to, int weight) {

	//create the new node and init. all of its attributes
	EDGE *new_end = malloc(sizeof(EDGE));
	new_end->from = from;
	new_end->to = to;
	new_end->weight = weight;
	new_end->next = NULL;

	//increase the size of the edgelist
	g->size++;

	//if the size is 0 then it is the first node to add to the list
	if (g->size == 0) {
		g->start = new_end;
		g->end = new_end;
	}

	//else if the size is 1 then start next, init end
	else if (g->size == 1) {
		g->end = new_end;
		g->start = g->end;

	}

	//add to the end
	else {
		g->end->next = new_end;
		g->end = g->end->next;
	}

}

void add_edge_start(EDGELIST *g, int from, int to, int weight) {

	//create the new node and init. all of its attributes
	EDGE *new_start = malloc(sizeof(EDGE));
	new_start->from = from;
	new_start->to = to;
	new_start->weight = weight;
	new_start->next = g->start; //we want to make the front this new node

	//increase the size of the edgelist
	g->size++;

	//if the edgelist is empty make it the only node
	if (g->size == 0) {
		g->start = new_start;
		g->end = new_start;

	} else
		g->start = new_start;

}

int weight_edgelist(EDGELIST *g) {

	//get the weight of everything in the edgelist
	int weight = 0;
	EDGE *curr = g->start;

	while (curr != NULL) {
		weight = weight + curr->weight;
		curr = curr->next;
	}

	return weight;
}

void clean_edgelist(EDGELIST **gp) {
	EDGELIST *g = *gp;
	EDGE *temp, *p = g->start;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	free(g);
	*gp = NULL;
}

void display_edgelist(EDGELIST *g) {
	if (g == NULL)
		return;
	printf("size:%d\n", g->size);
	printf("(from to weight):");
	EDGE *p = g->start;
	while (p) {
		printf("(%d %d %d) ", p->from, p->to, p->weight);
		p = p->next;
	}
}
