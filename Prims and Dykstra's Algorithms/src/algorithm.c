/*
 -------------------------------------
 File:    algorithm.c
 file description
 Prims and Dykstra's algorithms (using arrays)
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-04-09
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "algorithm.h"

EDGELIST* mst_prim(GRAPH *g, int start) {

	//if the graph is null do nothing
	if (g == NULL)
		return NULL;

	int i, heapindex;
	int n = g->order;				 //n is the number of nodes in the graph
	int treeNodesVisited[n], parent[n]; //treeNodesVisited[] represents nodes in current tree

	for (i = 0; i < n; i++) {
		treeNodesVisited[i] = 0; //set all the nodes visited to 0 by default
		parent[i] = -1; 		 // parent[i] represents parent of i
	}

	// set the first node of current tree from 'start' location
	treeNodesVisited[start] = 1;

	// for each neighbor, add corresponding heap node into heap
	ADJNODE *temp_curr = g->nodes[start]->neighbor;
	HNODE heapnode; 			 // temp heap node variable
	HEAP *newHeap = new_heap(4); // heap for finding minimum weight edge

	while (temp_curr) {
		heapnode.key = temp_curr->weight;
		heapnode.data = temp_curr->nid;
		insert(newHeap, heapnode);
		parent[temp_curr->nid] = start;
		temp_curr = temp_curr->next;
	}

	// create EDGELIST object to hold MST
	EDGELIST *mst = new_edgelist();

	// the main loop the Prim’s algorithm
	while (newHeap->size > 0) {

		heapnode = extract_min(newHeap); // get the minimum node
		i = heapnode.data; //grab the hashnode value
		treeNodesVisited[i] = 1; // add i to current tree
		add_edge_end(mst, parent[i], i, heapnode.key); // add to MST

		// update the keys of neighbors of the newly added node
		temp_curr = g->nodes[i]->neighbor;

		while (temp_curr) {
			heapindex = find_index(newHeap, temp_curr->nid);

			if (heapindex >= 0 && treeNodesVisited[temp_curr->nid] == 0 && temp_curr->weight < newHeap->hnap->key) {
				decrease_key(newHeap, heapindex, temp_curr->weight);
				parent[temp_curr->nid] = i;
			}

			//if the index of temp node is not in the tree nodes visited, add it
			if (heapindex < 0 && treeNodesVisited[temp_curr->nid] == 0) {
				heapnode.key = temp_curr->weight;
				heapnode.data = temp_curr->nid;
				insert(newHeap, heapnode);
				parent[temp_curr->nid] = i;
			}

			//move to the next neighbor in the graph
			temp_curr = temp_curr->next;
		}
	}

	return mst;
}

//compute Shortest Path Tree (traverse all nodes) by Dijkstra's algorithm using min-heap
EDGELIST* spt_dijkstra(GRAPH *g, int start) {

	//if the graph doesnt exist then exit
	if (!g)
		return NULL;

	int i, heapindex, hndata; // hndata is heapnode data, used in main loop
	int n = g->order;	//n is the number of nodes
	int treeNodesVisited[n];	//TreeNodesVisited represents nodes in current tree
	int parent[n];
	int setter[n];

	EDGELIST *spt = new_edgelist(); //edge list we want to return
	HNODE heapnode;

	for (i = 0; i < n; i++) {
		treeNodesVisited[i] = 0; //set all the nodes visited to 0 by default
		setter[i] = 9999;		 //set all of the setting nodes to a high number
	}

	// for each neighbor, add corresponding heap node into heap
	ADJNODE *temp_curr = g->nodes[start]->neighbor;
	HEAP *newHeap = new_heap(4);
	while (temp_curr) {
		heapnode.key = temp_curr->weight;
		heapnode.data = temp_curr->nid;
		insert(newHeap, heapnode);
		parent[temp_curr->nid] = start;
		temp_curr = temp_curr->next;
	}

	//main loop for dykstras path tree
	treeNodesVisited[start] = 1;
	setter[start] = 0;
	while (newHeap->size > 0) {

		//grab the minimum value from the heap
		heapnode = extract_min(newHeap);
		hndata = heapnode.data;

		//add to visited, add edge to edgelist
		treeNodesVisited[hndata] = 1;
		add_edge_end(spt, parent[hndata], hndata, heapnode.key);

		//look at all of the neighbors in the graph
		temp_curr = g->nodes[hndata]->neighbor;
		while (temp_curr) {

			heapindex = find_index(newHeap, temp_curr->nid);

			if (heapindex >= 0 && treeNodesVisited[temp_curr->nid] == 0 && temp_curr->weight + setter[hndata] < newHeap->hnap->key) {
				decrease_key(newHeap, heapindex, temp_curr->weight + setter[hndata]);
				parent[temp_curr->nid] = hndata;
			}

			//if the index of temp node is not in the tree nodes visited, add it
			else if (heapindex < 0 && treeNodesVisited[temp_curr->nid] == 0) {
				heapnode.key = temp_curr->weight;
				heapnode.data = temp_curr->nid;
				insert(newHeap, heapnode);
				parent[temp_curr->nid] = hndata;

			}

			//move to the next neighbor in the graph
			temp_curr = temp_curr->next;
		}
	}

	return spt; //return the list of edges that span the shortest path visiting all nodes
}

//compute Shortest Path by Dijkstra's algorithm using min-heap
EDGELIST* sp_dijkstra(GRAPH *g, int start, int end) {

	//if the graph doesnt exist then exit
	if (!g) {
		return NULL;
	}

	int i, heapindex, hndata;
	int n = g->order, parent[n]; //n is the number of nodes

	int treeNodesVisited[n]; // the tree nodes visited
	int setter[n];

	for (i = 0; i < n; i++) {
		treeNodesVisited[i] = 0; //set all the nodes visited to 0 by default
		setter[i] = 9999;		 //set all of the setter nodes to a high number
	}

	// for each neighbor, add corresponding heap node into heap
	ADJNODE *temp_curr = g->nodes[start]->neighbor;
	HNODE tempheapnode;
	HEAP *newHeap = new_heap(4);
	treeNodesVisited[start] = 1; //wherever we want to start we have visited

	while (temp_curr) {
		tempheapnode.key = temp_curr->weight;
		tempheapnode.data = temp_curr->nid;
		insert(newHeap, tempheapnode);
		parent[temp_curr->nid] = start;
		treeNodesVisited[temp_curr->nid] = 0;
		setter[temp_curr->nid] = temp_curr->weight;
		temp_curr = temp_curr->next;
	}

	//main loop for dykstras shortest path, get all of the paths
	setter[start] = 0;
	EDGELIST *spt = new_edgelist();
	while (newHeap->size > 0 && hndata != end) {

		//grab the minimum value from the heap
		HNODE heapnode = extract_min(newHeap);
		hndata = heapnode.data;

		//add to visited, add edge to edgelist
		treeNodesVisited[hndata] = 1;
		add_edge_end(spt, parent[hndata], hndata, setter[hndata] - setter[parent[hndata]]);

		//look at all of the neighbors in the graph
		temp_curr = g->nodes[hndata]->neighbor;
		HNODE hashnode_2;
		while (temp_curr) {

			//grab the index of the current value in the heap
			heapindex = find_index(newHeap, temp_curr->nid);

			if (heapindex >= 0 && treeNodesVisited[temp_curr->nid] == 0 && temp_curr->weight + setter[hndata] < newHeap->hnap->key) {
				decrease_key(newHeap, heapindex, temp_curr->weight + setter[hndata]);
				parent[temp_curr->nid] = hndata;
				setter[temp_curr->nid] = temp_curr->weight + setter[hndata];
			}

			//if the index of temp node is not in the tree nodes visited, add it
			else if (heapindex < 0 && treeNodesVisited[temp_curr->nid] == 0) {
				hashnode_2.key = temp_curr->weight + setter[hndata];
				hashnode_2.data = temp_curr->nid;
				insert(newHeap, hashnode_2);
				parent[temp_curr->nid] = hndata;
				setter[temp_curr->nid] = temp_curr->weight + setter[hndata];
			}

			//move to the next neighbor in the graph
			temp_curr = temp_curr->next;
		}
	}

	//now make a new edgelist and take the shortest path
	EDGELIST *sp = new_edgelist();
	sp->size = 0;
	while (hndata != start) {
		add_edge_start(sp, parent[hndata], hndata, setter[hndata] - setter[parent[hndata]]);
		hndata = parent[hndata];
	}

	return sp; //return the list of edges that span the shortest path from start to end
}

