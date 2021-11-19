/*
 -------------------------------------
 File:    heap.c
 file description
 Heap Data Structure Methods
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-31
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/* create and return a heap data structure
 to instantiate and return the pointer of the above heap structure,  size=0, capacity=4, allocate memory space to hold array of
 elements of the capacity and store pointer in data
 */
HEAP* new_heap(int capacity) {
	//blank heap with no nodes
	HEAP *heap = malloc(sizeof(HEAP));
	heap->capacity = capacity;
	heap->size = 0;
	heap->hnap = malloc(sizeof(HNODE) * capacity);
	return heap;
}

/* this inserts the given node data a into the heap; When the heap size is equal to the capacity, the inserting process
 * needs first to expand data array by doubling its amount. This may need to copy the data of old array to new array,
 * secondly insert the new data element into the end of the array, heapify and update size.*/
void insert(HEAP *heap, HNODE new_node) {

	//before insertion we need to check the size of the heap to avoid overflow
	if (heap->size == heap->capacity) {
		heap->capacity *= 2; //this is to reset to double the capacity
		HNODE *temp = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);

		if (temp) {
			heap->hnap = temp;
		} else {
			temp = malloc(sizeof(HNODE) * heap->capacity);

			if (temp) {
				memcpy(temp, heap->hnap, sizeof(HNODE) * heap->size);
				free(heap->hnap);
				heap->hnap = temp;
			} else
				printf("Resizing Heap Array Failure");
		}
	}

	//increase the size of the heap
	heap->size++;

	//insert the new element at the end of the heap
	heap->hnap[heap->size - 1] = new_node;

	//if the parent is smaller than the new_node then we want to heapify up
	int parent_index = (heap->size - 2) / 2;
	int child_index = heap->size - 1;

	if (heap->size > 1 && (cmp(heap->hnap[child_index].key, heap->hnap[parent_index].key) == -1))
		heapify_up(heap);
}

/* swap the data of two nodes in the heap */
void heap_swap(HNODE *a, HNODE *b)
//====================
{
	//swap the keys of the nodes
	KEYTYPE temp1 = a->key;
	a->key = b->key;
	b->key = temp1;

	//swap the data in the nodes
	DATA temp2 = a->data;
	a->data = b->data;
	b->data = temp2;

}

/* move the node up if it is smaller */
void heapify_up(HEAP *source) {

	//init the parent node and the child node position and data
	int parent_index = (source->size - 2) / 2;
	int child_index = source->size - 1;

	int parent_val = source->hnap[parent_index].key;
	int child_val = source->hnap[child_index].key;

	//swap the parent node and the current node
	while (child_val < parent_val && child_index != 0) {

		//swap the two nodes in the list
		heap_swap(&source->hnap[child_index], &source->hnap[parent_index]);

		//swap the current indices
		child_index = parent_index;
		parent_index = (child_index - 1) / 2;

		//grab the new comparable node values
		parent_val = source->hnap[parent_index].key;
		child_val = source->hnap[child_index].key;
	}
}

/* move the node down if it is bigger */
void heapify_down(HEAP *source) {

	//start from the bottom and sort from the bottom up
	//not the most efficient but I couldnt get the latter to work
	int run = 1;

	while (run == 1) { //while the child is less than the parent swap
		run = 0;
		for (int child_index = 0; child_index < source->size; child_index++) {

			int parent_index = (child_index - 1) / 2;

			if (source->hnap[child_index].key < source->hnap[parent_index].key) {
				heap_swap(&source->hnap[child_index], &source->hnap[parent_index]);
				run = 1;
			}

		}
	}
	/*
	 //init the parent node and the child node position and data
	 int curr = 0;
	 int child_index = (curr * 2) + 1; // left child
	 HNODE *val = &source->hnap[curr]; //the swapped node

	 while (child_index <= source->size) {

	 //find the smallest child
	 if ((child_index < source->size) && source->hnap[child_index].key > source->hnap[child_index + 1].key)
	 child_index++;

	 //if this condition runs then we are done heapifying
	 if (source->hnap[child_index].key >= val->key)
	 break;

	 //swap the nodes in the array otherwise
	 else {
	 heap_swap(&source->hnap[curr], &source->hnap[child_index]);
	 curr = child_index;
	 child_index = (curr * 2) + 1;

	 }
	 }
	 heap_swap(&source->hnap[curr], val);*/

}

/* this gets the data element of minimum key and delete the element from the binary heap. When the heap size  is no more
 * than a quarter of the capacity, it needs to shrink the data array by half to free the unused memory space. */
HNODE extract_min(HEAP *heap) {

	// step1: grab the min value to return (ie. index 0)
	HNODE extraction = heap->hnap[0];
	heap->hnap[0] = heap->hnap[heap->size - 1];
	heap->hnap[heap->size - 1].data = 0;
	heap->hnap[heap->size - 1].key = 0;
	heap->size--;

	if (heap->size > 0) {
		//step2: heapify_down.
		if ((cmp(heap->hnap[0].key, heap->hnap[1].key) == 1) || cmp(heap->hnap[0].key, heap->hnap[2].key) == 1)
			heapify_down(heap);

		//step3: remove extra capacity if the size of the array is less than 1/4
		if ((float) ((float) heap->size / (float) heap->capacity) * 100 <= 25)
			heap->capacity = heap->capacity / 4;

	}
	return extraction;

}

/* this decreases the key value of given element by index to new_key_value */
void decrease_key(HEAP *heap, int node_index, KEYTYPE key_value) {

	heap->hnap[node_index].key = key_value;

	int parent_index = (node_index - 2) / 2;
	int child_index = node_index;

//cant use heapify_up as we should be starting at where the node_index was
	if (heap->size > 1 && (cmp(heap->hnap[child_index].key, heap->hnap[parent_index].key) == -1)) {

		int parent_val = heap->hnap[parent_index].key;
		int child_val = heap->hnap[child_index].key;

		//swap the parent node and the current node
		while (child_val < parent_val && child_index != 0) {

			//swap the two nodes in the list
			heap_swap(&heap->hnap[child_index], &heap->hnap[parent_index]);

			//swap the current indices
			child_index = parent_index;
			parent_index = (child_index - 1) / 2;

			//grab the new comparable node values
			parent_val = heap->hnap[parent_index].key;
			child_val = heap->hnap[child_index].key;
		}

	}

}

/* this finds and returns the first index of heap node of given data d*/
int find_index(HEAP *heap, DATA value) {
	int index = 0;

//find the index of the data we want to find, if it exists
	int i = 0;
	while (heap->size > i && heap->hnap[i].data != value)
		i++;

//if it exists then we want to return that index
	if (heap->hnap[i].data == value)
		index = i;

	return index;
}

/* this displays data elements in heap by index ordering.  */
void display_heap(HEAP *hp) {
	printf("\nsize:%d\ncapacity:%d\n", hp->size, hp->capacity);
	printf("(index, key, data):\n");
	int i;
	for (i = 0; i < hp->size; i++) {
		printf("(%d %d %d) ", i, hp->hnap[i].key, hp->hnap[i].data);
		if (i % 10 == 9)
			printf("\n");
	}
	printf("\n");
}

/* this compare two key values a and b, return -1 if a<b, 0 if a=b, 1 if a>b  */
int cmp(KEYTYPE a, KEYTYPE b) {
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
