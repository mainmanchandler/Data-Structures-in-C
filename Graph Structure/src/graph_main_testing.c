#include <stdio.h>
#include "graph.h"

int main() {
	GRAPH *graph = new_graph(5);
	add_edge(graph, 0, 1, 7);
	add_edge(graph, 1, 0, 7);
	add_edge(graph, 0, 2, 3);
	add_edge(graph, 2, 0, 3);
	add_edge(graph, 1, 2, 4);
	add_edge(graph, 2, 1, 4);
	add_edge(graph, 2, 3, 10);
	add_edge(graph, 3, 2, 10);
	add_edge(graph, 1, 3, 9);
	add_edge(graph, 3, 1, 9);
	add_edge(graph, 1, 4, 11);
	add_edge(graph, 4, 1, 11);

	printf("display_graph():\n");
	display_graph(graph);

	printf("\nbf_traverse():");
	bf_traverse(graph, 0);

	printf("\ndf_traverse():");
	df_traverse(graph, 0);

	clean_graph(&graph);

	printf("\n");
	return 0;
}

