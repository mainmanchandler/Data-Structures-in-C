/*
 -------------------------------------
 File:    graph.h
 file description
 header file for the graph data structure
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-04-09
 -------------------------------------
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#define INFINITY 99999

/*
 * structure of adjacent node linked list
 * nid  - to node id
 * weight -  edge weight
 * next   - pointer to next adjnode
 */
typedef struct adjnode {
	int nid;
	int weight;
	struct adjnode *next;
} ADJNODE;

/*
 * structure of graph node
 * nid  - graph node id
 * neighbor - pointer to the linked list of neighbors
 */
typedef struct gnode {
	int nid;            // graph node id
	ADJNODE *neighbor;  // pointer to linked list of neighers
} GNODE;

/*
 * structure of adjacent list graph
 * order - number of nodes
 * size - number of edges
 * nodes - array of GNODE pointers
 */
typedef struct graph {
	int order;         // number of nodes
	int size;          // number of edges
	GNODE **nodes;     // pointer to an array of GNODE pointers
} GRAPH;

/* create and return a new adjacent list graph of order n */
GRAPH* new_graph(int n);

/* add a new edge (from, to, weight) to the graph passed by GRAPH *g,
 if the edge (from, to) exists, update its weight.
 */
void add_edge(GRAPH *g, int from, int to, int weight);

/* traverse and display node id by breadth-first order starting from nid */
void bf_traverse(GRAPH *g, int nid);

/* traverse and display node id by depth-first order starting from nid*/
void df_traverse(GRAPH *g, int nid);

// The implementation of the following functions are provided
int get_weight(GRAPH *g, int from, int to);
void display_graph(GRAPH *g);
void clean_graph(GRAPH **gp);

typedef struct queue_node {
	void *data;
	struct queue_node *next;
} QNODE;

typedef struct queue {
	QNODE *front, *rear;
} QUEUE;

void enqueue(QUEUE *qp, void *data);
void* dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

typedef struct stack_node {
	void *data; // pointer data
	struct stack_node *next;
} SNODE;

typedef struct stack {
	SNODE *top;
} STACK;

void push(STACK *sp, void *data);
void pop(STACK *sp);
void* peek(STACK *sp);
void clean_stack(STACK *sp);

#endif /* GRAPH_H_ */
