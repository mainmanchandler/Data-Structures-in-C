/*
-------------------------------------
File:    matrix.h
file description
header file for matrix.c
-------------------------------------
Author:  Chandler Mayberry
Version  2021-01-28
-------------------------------------
 */

#ifndef MATRIX_H_
#define MATRIX_H_

void display_matrix(int *m, int n);
int sum(int *m, int n);
int is_magic_square(int *m, int n);
void transpose_matrix(int *m1, int *m2, int n);
void multiply_matrix(int *m1, int *m2, int *m3, int n);

#endif /* MATRIX_H_ */
