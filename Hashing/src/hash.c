/*
 -------------------------------------
 File:    hash.c
 file description
 hashing function from scratch
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-29
 -------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int hash(char *word) {
	unsigned int hash = 0, i;
	for (i = 0; word[i] != '\0'; i++) {
		hash = 31 * hash + word[i];
	}
	return hash % htsize;
}

HTNODE* new_hashnode(char *name, int value) {

	//malloc space of the new node
	HTNODE *hashnode = (HTNODE*) malloc(sizeof(HTNODE));

	//fill in the values of the node
	strcpy(hashnode->name, name);
	hashnode->value = value;
	hashnode->next = NULL;

	return hashnode;

}

HASHTABLE* new_hashtable(int size) {

	//malloc the initial table size
	HASHTABLE *hashtable = (HASHTABLE*) malloc(sizeof(HASHTABLE));

	//make a linked array the size of size (10 by default)
	hashtable->hnp = (HTNODE**) malloc(sizeof(HTNODE**) * size);

	//fill the array and set the values to default
	for (int i = 0; i < size; i++)
		*(hashtable->hnp + i) = NULL; //init all of the nodes in the linked list array to null by default

	hashtable->size = size;
	hashtable->count = 0;

	return hashtable;
}

HTNODE* search(HASHTABLE *ht, char *name) {

	int i = hash(name);		//compute the hash index of name
	HTNODE *p = ht->hnp[i]; //get the linked list of the hash value

	//search the linked list, if name is matched return the node;
	while (p != NULL) {

		if (strcmp(p->name, name) != 0)
			p = p->next;
		else
			return p;
	}

	return NULL;
}

int insert(HASHTABLE *ht, HTNODE *np) {

	int success = 0;
	//grab the starting location to insert
	int start = hash(np->name);

	HTNODE *prev = NULL;
	HTNODE *curr = *(ht->hnp + start);

	//need to loop through array (if needed) and insert at the next empty location)
	if (curr != NULL) {

		//when looping we need to check if the same name is already in the list (duplicates)
		while (strcmp(curr->name, np->name) != 0 && curr != NULL) {
			prev = curr;
			curr = curr->next;
		}

		//if there is duplicate then we need to update the value of the node in the list
		if (strcmp(curr->name, np->name) == 0)
			curr->value = np->value;

		else { //perform insertion

			prev->next = np;
			np->next = curr;
			ht->count++;
			success = 1;
		}

	} else {
		//the first location checked was empty
		*(ht->hnp + start) = np;
		ht->count++;
		success = 1;
	}

	return success;
}

int delete(HASHTABLE *ht, char *name) {

	int success = 0;
	//grab the starting location to delete
	int start = hash(name);

	HTNODE *prev = NULL;
	HTNODE *curr = *(ht->hnp + start);

	//need to loop through array (if needed) and insert at the next empty location)
	if (curr != NULL) {

		//when looping we need to check if the same name is already in the list (duplicates)
		while (strcmp(curr->name, name) != 0 && curr != NULL) {
			prev = curr;
			curr = curr->next;
		}

		//if there is duplicate then we need to update the value of the node in the list
		if (strcmp(curr->name, name) == 0) {

			if (prev == NULL)
				*(ht->hnp + start) = NULL;
			else
				prev->next = curr->next;

			ht->count--;
			success = 1;
		}
	}

	free(curr);
	return success;

}

// you can use this function in your program
void clean_hash(HASHTABLE **htp) {
	if (*htp == NULL)
		return;
	HASHTABLE *ht = *htp;
	HTNODE *sp = ht->hnp[0], *p, *temp;
	int i;
	for (i = 0; i < ht->size; i++) {
		p = ht->hnp[i];
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		ht->hnp[i] = NULL;
	}
	free(ht->hnp);
	ht->hnp = NULL;
	*htp = NULL;
}

// you can use this function in your program
void display_hashtable(HASHTABLE *ht, int option) {
	int i = 0;
	HTNODE *p;
	if (option == 0) {
		printf("size:  %d\n", ht->size);
		printf("count: %d\n", ht->count);
		printf("hash data:\nindex: list of the data elements");
		for (i = 0; i < ht->size; i++) {
			p = *(ht->hnp + i);
			if (p)
				printf("\n%2d: ", i);

			while (p) {
				printf("(%s, %d) ", p->name, p->value);
				p = p->next;
			}
		}
		printf("\n");
	} else {

		for (i = 0; i < ht->size; i++) {
			p = *(ht->hnp + i);
			while (p) {
				printf("%s=%d\n", p->name, p->value);
				p = p->next;
			}
		}

	}

}
