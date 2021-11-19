/*
 -------------------------------------
 File:    edgelist.h
 file description
 edgelist header file with structures
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-04-09
 -------------------------------------
 */

#ifndef EDGELIST_H_
#define EDGELIST_H_

/*
 * edge structure
 */
typedef struct edge {
	int from;
	int to;
	int weight;
	struct edge *next;
} EDGE;

/*
 * edgelist graph structure
 * size  - number of edges
 * start - pointer to the first edge node
 * end   - pointer to the last edge node
 */
typedef struct edgelist {
	int size;
	EDGE *start;
	EDGE *end;
} EDGELIST;

/* create and return a new edge list graph*/
EDGELIST* new_edgelist();

/* add an new edge at the end of the linked list of edges*/
void add_edge_end(EDGELIST *g, int from, int to, int weight);

/* add an new edge at the start of the linked list of edges*/
void add_edge_start(EDGELIST *g, int from, int to, int weight);

/* get weight of the edge list graph*/
int weight_edgelist(EDGELIST *g);

/* display edge list graph*/
void display_edgelist(EDGELIST *g);

/* clean the graph by free all dynamically allocated memory*/
void clean_edgelist(EDGELIST **gp);

#endif /* EDGELIST_H_ */
