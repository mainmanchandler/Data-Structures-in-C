/*
 -------------------------------------
 File:    mysort.c
 file description
 Sorting algorithms
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-06
 -------------------------------------
 */

#include "mysort.h"

//double check this function later, the last element ~might~ be getting skipped.
/*This function tests if array a[n] is sorted in increasing order between index left and right, and returns true if yes, otherwise false.*/
BOOLEAN is_sorted(int *a, int left, int right) {
	int prev = 0;
	int sorted = 1;
	int counter = 0;

	while (counter <= right && prev <= *a) {

		if (counter == 0) {
			prev = *(a + counter);
		} else if (prev > *(a + counter)) {
			sorted = 0;
		}

		//printf("%d", *(a + counter));
		counter += 1;
	}
	//printf("\n");
	return sorted;
}

/*This function sorts the elements of int array *a from index left to right in increasing order, using the selection sort algorithm. */
void select_sort(int *a, int left, int right) {

	int i, j, k; //variables that loop through
	for (i = 0; i <= right; ++i) {

		k = i;
		for (j = i + 1; j <= right; ++j) {
			if (*(a + j) < *(a + k)) {
				k = j;
			}
		}
		if (i != k) {
			swap((a + k), (a + i));
		}
	}

	return;
}

/*This function sorts the elements of int array *a from index left to right in increasing order, using the quick sort algorithm. */
void quick_sort(int *a, int left, int right) {

	int pivot_key, midpoint;
	int i, j;
	if (left < right) {

		midpoint = (left + right) / 2;
		swap(a + left, a + midpoint); //swap the midpoint with the left n element

		pivot_key = *(a + left); //pivot key
		i = left;
		j = right;

		while (i < j) { //sort with current pivot

			while ((i < right) && (*(a + i) <= pivot_key)) //elements from left are less than or equal to the pivot key
				i++;
			while ((j > left) && (*(a + j) > pivot_key)) //elements to the right are greater than the pivot key
				j--;

			if (i < j) {
				//swap(&a[i], &a[j]); //different syntax, same thing
				swap(a + i, a + j); //if the value to the left is larger than the pivot, swap
			}

		}

		//swapping to new pivot value
		swap(a + j, a + left);

		//recurse back through the program
		quick_sort(a, left, j - 1);
		quick_sort(a, j + 1, right);

	}

	return;
}

/*This function swaps the values at referenced locations. It is an auxiliary function for the sorting functions.*/
void swap(int *first, int *second) {
	int temp = *first;
	*first = *second;
	*second = temp;
}

