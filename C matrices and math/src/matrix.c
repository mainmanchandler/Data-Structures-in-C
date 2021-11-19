/*
 -------------------------------------
 File:    matrix.c
 file description
 matrix methods
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-01-28
 -------------------------------------
 */

#include<stdio.h>
#include "matrix.h"

/*
 -------------------------------------------------------
 Displays the n by n matrix in 2d format.
 Use: display_matrix(int *m, int n)
 -------------------------------------------------------
 Parameters:
 *m - pointer to the first element in the matrix (pointer)
 n - length of the matrix: amount of columns (int)
 Returns:
 None
 -------------------------------------------------------
 */
void display_matrix(int *m, int n) {
	int *p = m, i, j; //initialize i and j and assigns value of the first element in the matrix to pointer
	for (i = 0; i < n; i++) {
		printf("\n");
		for (j = 0; j < n; j++)
			printf("%4d", *p++);
	}
	printf("\n");
}

/*
 -------------------------------------------------------
 computes and returns the sum of all elements of the n by n matrix m
 Use: sum(int *m, int n)
 -------------------------------------------------------
 Parameters:
 *m - pointer to the first element in the matrix (pointer)
 n - length of the matrix: amount of columns (int)
 Returns:
 sum - sum of the 2d matrix
 -------------------------------------------------------
 */
int sum(int *m, int n) {
	int sum;

	int *p = m, row, col; //initialize i and j and assigns value of the first element in the matrix to pointer
	for (row = 0; row < n; row++) {
		for (col = 0; col < n; col++) {
			sum += *p++;
		}
	}

	return sum;
}

/*
 -------------------------------------------------------
 Computes and returns if the n by n matrix m is a magic square.
 Returns 1 if true or zero if false. A square matrix is a magic square
 if the sum of every row, column, and diagonal is of the same magic constant rowsum.
 Use: is_magic_square(int *m, int n)
 -------------------------------------------------------
 Parameters:
 *m - pointer to the first element in the matrix (pointer)
 n - length of the matrix: amount of columns (int)
 Returns:
 is_magic - returns 1 if true, 0 if false
 -------------------------------------------------------
 */
int is_magic_square(int *m, int n) {
	//There are n rows, n columns, and 2 diagonals to check.
	//p[row][col]

	//init variables
	int is_magic = 1, row_val = 0, col_val = 0; //row and column values and comparison variables
	int left_to_right = 0, right_to_left = 0; //diagonals across the matrix
	int rowsum = n * (n * n + 1) / 2; //rowsum of the 3x3 is 15
	int *q = m, *p = m, i, j, row, col; //two pointers to matrix m values and looping variables

	for (row = 0, j = 0; row < n; row++, j++) {
		row_val = 0;
		col_val = 0;

		for (col = 0, i = 0; col < n; col++, i++) {

			if (row == n - (i + 1)) { //backwards diagonal
				right_to_left += *p;
			}
			if (i == j) { //forwards diagonal
				left_to_right += *q;
			}

			row_val += *p++;
			col_val += *q++;
		}
		if (row_val != rowsum || col_val != rowsum) {
			is_magic = 0;
		}
	}
	if (right_to_left != rowsum || left_to_right != rowsum) {
		is_magic = 0;
	}

	return is_magic;
}
/*
 -------------------------------------------------------
 Transposes the n by n matrix m1 and save the resulted matrix in m2
 Use: transpose_matrix(int *m1, int *m2, int n)
 -------------------------------------------------------
 Parameters:
 *m1 - pointer to the first element in the matrix (pointer)
 *m2 - pointer to the first element in the blank matrix (pointer)
 n - length of the matrix: amount of columns (int)
 Returns:
 none
 -------------------------------------------------------
 */
void transpose_matrix(int *m1, int *m2, int n) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			*(m2 + col * n + row) = *(m1 + row * n + col);
		}
	}
	return;
}

/*
 -------------------------------------------------------
 Computes the matrix multiplication m1*m2 and saves the resulted matrix in m3
 Use: multiply_matrix(int *m1, int *m2, int *m3, int n)
 -------------------------------------------------------
 Parameters:
 *m1 - pointer to the first element in the matrix (pointer)
 *m2 - pointer to the first element in the blank matrix (pointer)
 n - length of the matrix: amount of columns (int)
 Returns:
 none
 -------------------------------------------------------
 */
void multiply_matrix(int *m1, int *m2, int *m3, int n) {
	int temp;
	for (int row = 0; row < n; row++) {

		for (int col = 0; col < n; col++) {

			temp = 0;
			for (int i = 0; i < n; i++) {
				temp += *(m1 + row * n + i) * *(m2 + i * n + col);
			}

			*(m3 + row * n + col) = temp;
		}
	}
	return;
}

