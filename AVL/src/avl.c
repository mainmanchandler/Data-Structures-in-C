/*
 -------------------------------------
 File:    avl.c
 file description
 AVL BST methods
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-15
 -------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

// A utility functions
int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(TNODE *np) {

	int height = 0;

	//if the node exists, grab the height
	if (np)
		height = np->height;

	return height;
}

int balance_factor(TNODE *np) {
	int balancef = 0;

	//if the node exists, derived the balance factor
	if (np)
		balancef = height(np->left) - height(np->right);

	return balancef;
}

/* check if the tree is AVL tree, return 1 if true, 0 otherwise */
int is_avl(TNODE *root) {

	//we can check the validity by looking at the height at the left side of the tree
	//and the right side of the tree. If they are >+1 then the avl tree is invalid
	int valid = 0;

	if (root == NULL)
		valid = 1;
	else {
		int lheight = 0, rheight = 0;

		//get the height of the left and right subtrees
		//must call the function or will cause a stack dump if one is null
		lheight = height(root->left);
		rheight = height(root->right);

		//perform a recursive call to check all subtrees in the avl tree
		if (abs(lheight - rheight) < 2 && is_avl(root->left) && is_avl(root->right))
			valid = 1;
		else {
			valid = 0;
		}

	}
	return valid;

}

TNODE* rotate_right(TNODE *y) {

	//y is the rotation node

	TNODE *lptr = y->left;	//left pointer (to be new parent)
	TNODE *lrptr = lptr->right; //left->right pointer (new left child of y)

	//perform the rotation

	lptr->right = y; 	// make the new parent (replace y)
	y->left = lrptr; 	// make old parents new left pointer the old right child of new parent

	//change the height values
	y->height = max(height(y->left), height(y->right)) + 1;
	lptr->height = max(height(lptr->left), height(lptr->right)) + 1;

	return lptr;

}

TNODE* rotate_left(TNODE *x) {
	//x is the rotation node

	TNODE *lptr = x->right;	//left pointer (to be new parent)
	TNODE *lrptr = lptr->left; //left->right pointer (new right child of x)

	//perform the rotation
	lptr->left = x; 	// make the new parent (replace x)
	x->right = lrptr;	// make old parents new right pointer the old left child of new parent

	//change the height values
	x->height = max(height(x->left), height(x->right)) + 1;
	lptr->height = max(height(lptr->left), height(lptr->right)) + 1;

	return lptr;
}

void insert(TNODE **rootp, char *name, float score) {
	TNODE *np = (TNODE*) malloc(sizeof(TNODE));
	if (np == NULL)
		return;
	strcpy(np->data.name, name);
	np->data.score = score;
	np->height = 1;
	np->left = NULL;
	np->right = NULL;

	// 1. Perform the normal BST insertion
	if (*rootp == NULL) {
		*rootp = np;
		return;
	}

	TNODE *root = *rootp;
	if (strcmp(name, root->data.name) < 0)
		insert(&root->left, name, score);

	else if (strcmp(name, root->data.name) > 0)
		insert(&root->right, name, score);

	else
		return;

	// 2. update height of this root node

	root->height = 1 + max(height(root->left), height(root->right));

	// 3. Get the balance factor of this ancestor node to check whether this node became unbalanced

	int balancef = balance_factor(root);
	if (balancef >= -1 && balancef <= 1) //if the balancing factor is 1,0,-1 then we can skip the next
		return;

	// 4. re-balance if not balanced

	//If the height is greater than or equal to 2
	else if (balancef >= 2 && balance_factor(root->left) >= 0)		//case 1: do right rotation
		*rootp = rotate_right(root);

	else if (balancef >= 2 && balance_factor(root->left) < 0) { 	//case 2: do left-right rotation
		root->left = rotate_left(root->left);   //send the left child of the root to the rotate left
		*rootp = rotate_right(root);			//then rotate right using the root to complete rotation
	}

	//if the height is less than or equal to -2
	else if (balancef <= -2 && balance_factor(root->left) <= 0)	//case 3: do left rotation
		*rootp = rotate_left(root);

	else if (balancef <= -2 && balance_factor(root->left) > 0) {	//case 4: do right-left rotation
		*rootp = rotate_right(root->right);		//send the right child of the root to the rotate right
		*rootp = rotate_left(root);				//then rotate left using the root to complete rotation
	}
}

void delete(TNODE **rootp, char *name) {
	TNODE *root = *rootp;
	TNODE *np;

	if (root == NULL)
		return;

	//step 1; this performs the initial deletion
	if (strcmp(name, root->data.name) == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			*rootp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*rootp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*rootp = np;
		} else if (root->left != NULL && root->right != NULL) {
			np = extract_smallest_node(&root->right);
			np->left = root->left;
			np->right = root->right;
			free(root);
			*rootp = np;
		}
	} else {
		if (strcmp(name, root->data.name) < 0) {
			delete(&root->left, name);
		} else {
			delete(&root->right, name);
		}
	}

	// If the tree had only one node then return
	if (*rootp == NULL)
		return;

	root = *rootp;

	// STEP 2: update the this root node's height

	root->height = 1 + max(height(root->left), height(root->right));

	// STEP 3: get the balance factor of this root node

	int balancef = balance_factor(root);
	if (balancef >= -1 && balancef <= 1) //if the balancing factor is 1,0,-1 then we can skip the next
		return;

	// STEP 4: re-balance if not balanced

	//will be the same balancing technique as insert
	//If the height is greater than or equal to 2
	else if (balancef >= 2 && balance_factor(root->left) >= 0)		//case 1: do right rotation
		*rootp = rotate_right(root);

	else if (balancef >= 2 && balance_factor(root->left) < 0) { 	//case 2: do left-right rotation
		root->left = rotate_left(root->left);   //send the left child of the root to the rotate left
		*rootp = rotate_right(root);			//then rotate right using the root to complete rotation
	}

	//if the height is less than or equal to -2
	else if (balancef <= -2 && balance_factor(root->right) <= 0)	//case 3: do left rotation
		*rootp = rotate_left(root);

	else if (balancef <= -2 && balance_factor(root->right) > 0) {	//case 4: do right-left rotation
		*rootp = rotate_right(root->right);		//send the right child of the root to the rotate right
		*rootp = rotate_left(root);				//then rotate left using the root to complete rotation
	}

}

// following functions are from bst.c of a7
TNODE* extract_smallest_node(TNODE **rootp) {
	TNODE *tnp = *rootp;
	TNODE *parent = NULL;
	if (tnp == NULL) {
		return NULL;
	} else {
		while (tnp->left) {
			parent = tnp;
			tnp = tnp->left;
		}
		if (parent == NULL)
			*rootp = tnp->right;
		else
			parent->left = tnp->right;
		tnp->left = NULL;
		tnp->right = NULL;
		return tnp;
	}
}

TNODE* search(TNODE *root, char *name) {
	TNODE *tp = root;
	while (tp) {
		if (strcmp(name, tp->data.name) == 0) {
			return tp;
		} else if (strcmp(name, tp->data.name) < 0)
			tp = tp->left;
		else
			tp = tp->right;
	}
	return NULL;
}

void clean_tree(TNODE **rootp) {
	if (*rootp) {
		TNODE *np = *rootp;
		if (np->left)
			clean_tree(&np->left);
		if (np->right)
			clean_tree(&np->right);
		free(np);
	}
	*rootp = NULL;
	;
}

void display_inorder(TNODE *root) {
	if (root) {
		if (root->left)
			display_inorder(root->left);
		printf("(%s %3.1f) ", root->data.name, root->data.score);
		if (root->right)
			display_inorder(root->right);
	}
}

void display_inorder_lines(TNODE *root) {
	if (root) {
		if (root->left)
			display_inorder_lines(root->left);
		printf("%-15s%.1f\n", root->data.name, root->data.score);
		if (root->right)
			display_inorder_lines(root->right);
	}
}

void display_tree(TNODE *root, int prelen) {
	if (root) {
		int i;
		for (i = 0; i < prelen; i++)
			printf("%c", ' ');
		printf("%s", "|___");
		printf("%s %.1f %d\n", root->data.name, root->data.score, root->height);
		display_tree(root->right, prelen + 4);
		display_tree(root->left, prelen + 4);
	}
}
