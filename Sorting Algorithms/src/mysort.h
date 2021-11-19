/*
 -------------------------------------
 File:    mysort.h
 file description
 Header file for the mysort function
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-06
 -------------------------------------
 */

#ifndef MYSORT_H_
#define MYSORT_H_

#ifndef MYSORT_H
#define MYSORT_H

// define enum type BOOLEAN
typedef enum {
	false = 0, true = 1
} BOOLEAN;

//enum BOOLEAN is_sorted(int *a, int left, int right);
void select_sort(int *a, int left, int right);
void quick_sort(int *a, int left, int right);
void swap(int *first, int *second);

#endif

#endif /* MYSORT_H_ */
