/*
 -------------------------------------
 File:    hash.h
 file description
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-29
 -------------------------------------
 */

#ifndef HASH_H_
#define HASH_H_

extern int htsize;

typedef struct hashnode {
	char name[10];  // used as key variable
	int value;
	struct hashnode *next;
} HTNODE;

typedef struct hashtable {
	HTNODE **hnp;    // pointer pointing to the array of hashnode pointers
	int size;          // hash table size, maximum number of different indices
	int count;         // number of data elements in the hash table
} HASHTABLE;

// hash is used to make the hash value that we can use to store/compare
int hash(char *name);

// creates a new hashnode for the hash array
HTNODE* new_hashnode(char *name, int vale);

// creates a new linked hash table array
HASHTABLE* new_hashtable(int size);

// searches for the wanted node if it exists
HTNODE* search(HASHTABLE *ht, char *name);

// inserts a node into the hash table
int insert(HASHTABLE *ht, HTNODE *np);

// deletes a node in the hash table
int delete(HASHTABLE *ht, char *name);

// clean up has
void clean_hash(HASHTABLE **htp);

// displays the hashtable
void display_hashtable(HASHTABLE *ht, int option);

#endif /* HASH_H_ */
