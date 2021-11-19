/*
-------------------------------------
File:    marks_avl.h
file description
marks_avl.c header and imports
-------------------------------------
Author:  Chandler Mayberry
Version  2021-03-16
-------------------------------------
 */

#ifndef MARKS_AVL_H_
#define MARKS_AVL_H_

#include "avl.h"
//these need to be included for the marks_avl.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct mark_stats {
    TNODE *bst;
    int count;
    float mean;
    float stddev;
} MARKS;

/* merge tree rootp2 into tree rootp1 */
void merge_tree(TNODE **rootp1, TNODE **rootp2); 

/* merget two MARKS dataset and aggregate stats info */
void merge_data(MARKS  *ds1, MARKS *ds2);

// the following functions are from a7q2
void display_stats(MARKS *dsp); 
void add_data(MARKS *dsp, char *name, float score);
void remove_data(MARKS *dsp, char *name);
void import_data(MARKS *dsp, char *filename);
void report_data(MARKS *dsp, char *filename);
void print_to_file_inorder(TNODE *root, FILE *filename);
void display_marks(MARKS *dsp);
void clean_marks(MARKS *dsp);
char letter_grade(float score);


#endif /* MARKS_AVL_H_ */
