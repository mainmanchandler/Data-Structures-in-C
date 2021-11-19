/*
-------------------------------------
File:    marks_bst.h
file description
marks bst header
-------------------------------------
Author:  Chandler Mayberry
Version  2021-03-11
-------------------------------------
 */

#ifndef MARKS_BST_H
#define MARKS_BST_H

#include "bst.h"

typedef struct marks_stats {
    TNODE *bst;
    int count;
    float mean;
    float stddev;
} MARKS;

/* add a record (name, score) into the bst and update the stats info incrementally */
void add_data(MARKS *dsp, char *name, float score);

/* delete a record of name from the bst and update the stats info incrementally */
void remove_data(MARKS *dsp, char *name);

char letter_grade(float score);
void import_data(MARKS *dsp, char *filename);
void report_data(MARKS *dsp, char *filename);
void print_to_file_inorder(TNODE *root, FILE *filename);
void display_marks(MARKS *dsp);
void clean_marks(MARKS *dsp);

#endif /* MARKS_BST_H_ */
