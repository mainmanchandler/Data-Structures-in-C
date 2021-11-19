/*
 -------------------------------------
 File:    bst.c
 file description
 binary search tree methods
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

TNODE* search(TNODE *root, char *name) {
	//answer is basically given in the notes

	TNODE *curr = root;
	int found = 0;
	while (curr && found == 0) {
		if (strcmp(curr->data.name, name) == 0) //name is found in the tree
			found = 1;
		else if (strcmp(curr->data.name, name) > 0) //name is <
			curr = curr->left;
		else
			curr = curr->right;
	}

	return curr; //if curr is null then the value was never found
}

void insert(TNODE **rootp, char *name, float score) {
	//answer is basically given in the notes
	//if a name is not given then dont run
	if (*name == '\0')
		return;

	//new node init
	TNODE *new = (TNODE*) malloc(sizeof(TNODE));
	strncpy(new->data.name, name, 39);
	new->data.score = score;
	new->left = NULL;
	new->right = NULL;

	if (*rootp == NULL)
		*rootp = new; //make the new root

	else {
		//get a curr and prev node to iterate through the tree
		TNODE *prev = NULL, *curr = *rootp;

		//iterate through the tree to find the spot to place the value,
		//while saving the prev (parent node)
		while (curr) {

			prev = curr;

			if (strcmp(curr->data.name, name) == 0) {
				//same value
				printf("this person is already in the table");
				return;

			} else if (strcmp(curr->data.name, name) < 0)
				//greater than move right
				curr = curr->right;

			else
				//less than move left
				curr = curr->left;

		}

		//push the new node to the left of the right of the parent.
		if (strcmp(prev->data.name, name) < 0)
			prev->right = new;
		else
			prev->left = new;

	}

	return;
}

void delete(TNODE **rootp, char *name) {
	//ah yes, my old friend. Delete >:(
	//thank you hbf, the notes literally gave me the answer, you are a G. Cheerio,

	TNODE *curr = *rootp, *prev = NULL, *smallest_node;

	//need to find the node to delete >:(
	while (curr != NULL && strcmp(curr->data.name, name) != 0) {
		prev = curr;
		curr = (strcmp(curr->data.name, name) < 0 ? curr->right : curr->left);
	}

	if (curr == NULL) {
		printf("the person you want to absolutely destroy from this bst is like not here dude");

	} else {
		if (curr->left == NULL) { //if the left of the parent node is NONE then an easy swap with the right is new parent

			//if prev is NULL then its the root
			if (prev == NULL)
				*rootp = curr->right;

			else {
				if (prev->left == curr)
					prev->left = curr->right;
				else
					prev->right = curr->right;
			}

		} else if (curr->right == NULL) { //if the right of the parent node is NONE then an easy swap with the left is new parent

			//if prev is NULL then its the root
			if (prev == NULL)
				*rootp = curr->left;

			else {
				if (prev->left == curr)
					prev->left = curr->left;
				else
					prev->right = curr->left;

			}

		} else { //if the node is a parent with two children, then we need to perform a right child, smallest node swap.
			smallest_node = extract_smallest_node(&curr->right);

			//if prev is NULL then its the root
			if (prev == NULL)
				*rootp = smallest_node;

			else {
				if (prev->left == curr)
					prev->left = smallest_node;
				else
					prev->right = smallest_node;
			}

			//this is the tricky part
			smallest_node->left = curr->left;
			smallest_node->right = curr->right;

		}
		free(curr); //free the current node, may he be remembered as the node I buried 6ft under
	}

}

/**this will extract the smallest node in the right sub-tree that we will have to
 * use as the new parent, if, the parent of some children needs to be deleted
 */
TNODE* extract_smallest_node(TNODE **rootp) {
	TNODE *prev = NULL, *curr = *rootp;

	//if the root (right node) exists find the farthest left of the right child node
	if (*rootp != NULL) {
		prev = curr;

		//find the farthest child node for the right node
		while (curr->left != NULL) {
			prev = curr;
			curr = curr->left;
		}

		if (prev == NULL)
			*rootp = curr->right;
		else
			prev->left = curr->right;

	}
	return curr;
}

void display_inorder(TNODE *root) {
	if (root) {
		if (root->left)
			display_inorder(root->left);
		printf("%-15s%3.1f\n", root->data.name, root->data.score);
		if (root->right)
			display_inorder(root->right);
	}
}

void clean_tree(TNODE **rootp) {
	TNODE *root = *rootp;
	if (root) {
		if (root->left)
			clean_tree(&root->left);
		if (root->right)
			clean_tree(&root->right);
		free(root);
	}
	*rootp = NULL;
}
