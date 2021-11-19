#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int main(int argc, char *args[]) {
	int c = 4;  // initial capacity
	int n = 10; // max size for testing
	int v = 6;  // data vale to find for index
	int k = 2;  // new decrease value
	int i;

	// get and set the testing parameters from command line arguments
	if (argc > 1) {
		c = atoi(args[1]);
	}
	if (argc > 2) {
		n = atoi(args[2]);
	}
	if (argc > 3) {
		v = atoi(args[3]);
	}
	if (argc > 4) {
		k = atoi(args[4]);
	}

	// create heap
	HEAP *hp = new_heap(c);
	if (hp->hnap == NULL)
		return 0;

	display_heap(hp);

	printf("insert to heap:\n");
	HNODE hd;
	for (i = 1; i <= n; i++) {
		hd.key = n - i + 4;
		hd.data = i;
		insert(hp, hd);
	}

	printf("display heap after insertion:");
	display_heap(hp);

	i = find_index(hp, v);
	printf("the index of data value %d is %d\n", v, i);
	printf("decrease key value at index %d to %d", i, k);
	decrease_key(hp, i, k);
	display_heap(hp);

	printf("call extract_min for %d times:", 4 * n / 5);
	for (i = 0; i < 4 * n / 5; i++) {
		hd = extract_min(hp);
		printf("(%d %d) ", hd.key, hd.data);
	}

	printf("\ndisplay heap after extract min:");
	display_heap(hp);

	return 0;
}

/*
 gcc heap.h heap.c a9q1.c -o a9q1
 a9q1 4 10 6 2

 size:0
 capacity:4
 (index, key, data):

 insert to heap:
 display heap after insertion:
 size:10
 capacity:16
 (index, key, data):
 (0 4 10) (1 5 9) (2 8 6) (3 7 7) (4 6 8) (5 12 2) (6 9 5) (7 13 1) (8 10 4) (9 11 3)

 the index of data value 6 is 2
 decrease key value at index 2 to 2
 size:10
 capacity:16
 (index, key, data):
 (0 2 10) (1 5 9) (2 4 10) (3 7 7) (4 6 8) (5 12 2) (6 9 5) (7 13 1) (8 10 4) (9 11 3)

 call extract_min for 8 times:
 (2 10) (4 10) (5 9) (6 8) (7 7) (9 5) (10 4) (11 3)
 display heap after extract min:
 size:2
 capacity:4
 (index, key, data):
 (0 12 2) (1 13 1)
 */

