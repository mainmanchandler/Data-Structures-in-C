/*
 -------------------------------------
 File:    myrecord_llist.c
 file description
 linked list data structure methods
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-15
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "myrecord_llist.h"

/**
 * Display linked list.
 * @param start Pointer to the first node of linked list.
 */
void display(NODE *start) {
	NODE *np = start;
	while (np != NULL) {
		printf("%s,%.1f\n", np->data.name, np->data.score);
		np = np->next;
	}
}

/**
 * Search linked list for name key.
 * @param start Pointer to the first node of linked list.
 * @param name Key to search
 * @return Pointer to found node if found; otherwise NULL
 */
NODE* search(NODE *startp, char *name) {

	NODE *found = NULL;
	NODE *currentp = startp;
	while (currentp != NULL) {

		if (strcmp(currentp->data.name, name) == 0) {
			found = currentp;
		}

		currentp = currentp->next;
	}

	return found;

}

/**
 * Insert new record to linked list at the sorted position.
 * @param startp Pointer pointing to the start pointer of linked list, used to update the start node address in case of change.
 * @param name The name data of new record.
 * @param score The score data of new record
 */
void insert(NODE **startp, char *name, float score) {
	//**startp -> *startp -> head
	//allocate space for the new node
	NODE *new = (NODE*) malloc(sizeof(NODE));
	strcpy(new->data.name, name); //assign the string to the new node
	new->data.score = score;
	new->next = NULL;

	//traversing nodes
	NODE *currentp = *startp;
	NODE *prev = NULL;

	//while not the end of the list
	//stops in alphabetical order (where its organized) in the list. ie. moore after lamont, before myrie
	while (currentp != NULL && strcmp(currentp->data.name, name) < 0) {
		prev = currentp;
		currentp = currentp->next;
	}

	//if prev is Null then the loop never ran, new node is the first node
	if (prev == NULL) {
		*startp = new;
		new->next = currentp;

	} else {
		//loop ran, therefore insert between prev and traversed location
		prev->next = new;
		new->next = currentp;
	}

	return;
}

/**
 * Delete a record by name from linked list, the first one matched.
 * @param startp Pointer pointing to the start pointer of linked list, used to update the start node address in case of change.
 * @param name  The key used to find the node for deletion.
 */
int delete(NODE **startp, char *name) {

	int check = 0;
	//traversing nodes
	NODE *currentp = *startp;
	NODE *prev = NULL;

	//run until it finds the node, or hits the end of the list
	//if its found, stop at location
	while (currentp != NULL && strcmp(currentp->data.name, name) != 0) {
		prev = currentp;
		currentp = currentp->next;
	}

	//if currentp != Null then its exists; delete the node
	if (currentp != NULL && strcmp(currentp->data.name, name) == 0) {
		prev->next = currentp->next;
		free(currentp); //free the memory location of the deleted node
		check = 1;
	}

	return check; //bruh why is this an int function
}

/**
 * Clean linked list.
 * @param startp Pointer pointing to the start pointer of linked list, used to update the start node address in case of change.
 */
void clean(NODE **startp) {

	NODE *currentp = *startp;
	NODE *prev = NULL;

	while (currentp != NULL) {
		prev = currentp;
		currentp = currentp->next;
		free(prev);
	}
	*startp = NULL;

	return;
}

// the following functions are adapted and modified from previous assignments.

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

int import_data(NODE **startp, char *filename) {
	char line[40], name[20];
	char *result = NULL;
	char delimiters[] = ",";
	float score = 0;
	int count = 0;

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		result = strtok(line, delimiters);
		strcpy(name, result);
		result = strtok(NULL, delimiters);
		score = atof(result);
		insert(startp, name, score);
		count++;
	}
	fclose(fp);

	return count;
}

REPORT report_data(NODE *start, char *filename) {
	REPORT report = { };
	NODE *np = start;
	int count = 0;
	float mean = 0;
	float stddev = 0;

	FILE *fp = fopen(filename, "w");
	while (np != NULL) {
		count++;
		mean += np->data.score;
		stddev += np->data.score * np->data.score;
		fprintf(fp, "%s,%3.1f,%c\n", np->data.name, np->data.score, letter_grade(np->data.score));
		np = np->next;
	}
	fclose(fp);

	mean /= count;
	stddev = sqrt(stddev / count - mean * mean);
	report.count = count;
	report.mean = mean;
	report.stddev = stddev;
	return report;
}
