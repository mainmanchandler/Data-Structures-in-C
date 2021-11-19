/*
 -------------------------------------
 File:    marks_bst.c
 file description
 marks bst parent structure methods
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-11
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bst.h"
#include "marks_bst.h"

void add_data(MARKS *dsp, char *name, float score) {

	//need to search to make sure that the value isnt there already
	//if the value isnt there we can insert a new node into the tree
	if (search(dsp->bst, name) == NULL) {

		insert(&dsp->bst, name, score);

		//need to update the mean, stddev and count
		float m = dsp->mean;
		int n = dsp->count;
		float st = dsp->stddev;

		//perform calculations
		dsp->count = n + 1;  //new count
		dsp->mean = (m * n + score) / (n + 1); //new mean
		dsp->stddev = sqrt(score * score / (n + 1.0) + ((st * st) + (m * m)) * (n / (n + 1.0)) - (dsp->mean * dsp->mean)); //new stddev, also bro I hate calculations

	}
}

void remove_data(MARKS *dsp, char *name) {

	//only remove if it is found
	if (search(dsp->bst, name) != NULL) {

		//need to update the mean, stddev and count
		float m = dsp->mean;
		int n = dsp->count;
		float st = dsp->stddev;
		float score = (search(dsp->bst, name)->data.score); //get the score of the node we want to delete

		//perform calculations
		dsp->mean = (m * n - score) / (n - 1); //new mean
		dsp->stddev = sqrt(((score * score / (n - 1.0)) * -1) + ((st * st) + (m * m)) * (n / (n - 1.0)) - (dsp->mean * dsp->mean)); //new stddev, also bro I hate calculations

		dsp->count = n - 1;  //new count
		delete(&dsp->bst, name); //air strike the node

	}
}

// the following are adopted and modified from previous assignments
char letter_grade(float s) {
	char r = 'F';
	if (s >= 90)
		r = 'S';
	else if (s >= 80)
		r = 'A';
	else if (s >= 70)
		r = 'B';
	else if (s >= 60)
		r = 'C';
	else if (s >= 50)
		r = 'D';
	else
		r = 'F';
	return r;
}

void display_marks(MARKS *dsp) {
	printf("%-15s%d\n", "count", dsp->count);
	printf("%-15s%3.1f\n", "mean", dsp->mean);
	printf("%-15s%3.1f\n", "stddev", dsp->stddev);
	display_inorder(dsp->bst);
}

void clean_marks(MARKS *dsp) {
	clean_tree(&dsp->bst);
	dsp->count = 0;
	dsp->mean = 0;
	dsp->stddev = 0;
}

void import_data(MARKS *ds, char *filename) {
	char line[40], name[20];
	FILE *fp = fopen(filename, "r");
	char *result = NULL;
	float score = 0;
	char delimiters[] = ",\n";

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		result = strtok(line, delimiters);
		if (result) {
			strcpy(name, result);
			result = strtok(NULL, delimiters);
			score = atof(result);
			add_data(ds, name, score);
		}
	}
	fclose(fp);
}

void print_to_file_inorder(TNODE *root, FILE *fp) {
	if (root) {
		if (root->left)
			print_to_file_inorder(root->left, fp);
		fprintf(fp, "%s,%3.1f,%c\n", root->data.name, root->data.score, letter_grade(root->data.score));
		if (root->right)
			print_to_file_inorder(root->right, fp);
	}
}

void report_data(MARKS *dsp, char *filename) {
	FILE *fp = fopen(filename, "w");
	fprintf(fp, "%s:%d\n", "count", dsp->count);
	fprintf(fp, "%s:%.0f\n", "mean", dsp->mean);
	fprintf(fp, "%s:%.0f\n", "stddev", dsp->stddev);
	print_to_file_inorder(dsp->bst, fp);
	fclose(fp);
}
