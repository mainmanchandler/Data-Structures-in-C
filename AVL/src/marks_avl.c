/*
 -------------------------------------
 File:    marks_avl.c
 file description
 Marks AVL Methods - using avl.c
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-15
 -------------------------------------
 */

#include "marks_avl.h"

void merge_tree(TNODE **rootp1, TNODE **rootp2) {

	if (rootp2 == NULL) //if the node we try to send next is NULL then we are done
		return;
	else {
		// get data of each node and insert into rootp1
		insert(rootp1, (*rootp2)->data.name, (*rootp2)->data.score);

		// use recursive algorithm to traverse tree rootp2,
		//go left
		if ((*rootp2)->left != NULL)
			merge_tree(rootp1, &(*rootp2)->left);

		//go right
		if ((*rootp2)->right != NULL)
			merge_tree(rootp1, &(*rootp2)->right);
	}

}

void merge_data(MARKS *ds1, MARKS *ds2) {
	// call the merge_tree function to merge ds2->bst into da1->bst
	merge_tree(&ds1->bst, &ds2->bst); //aux will do the legwork, bst is the root of node in tree

	// update the stats of the merged data set using the stats of ds1 and ds2.
	// ie. update the mean, stddev, and count

	float m1 = ds1->mean; 		//tree1 mean
	float m2 = ds2->mean;		//tree2 mean
	int n1 = ds1->count;		//tree1 count
	int n2 = ds2->count;		//tree2 count
	float st1 = ds1->stddev;	//tree1 standard deviation
	float st2 = ds2->stddev;	//tree2 standard deviation

	int nt = n1 + n2; //total count

	//perform calculations for new merge:

	ds1->count = nt;  							//new total count
	ds1->mean = ((m1 * n1) + (m2 * n2)) / nt;	//new mean

	float new_mean = ds1->mean; //temp mean variable
	ds1->stddev = sqrt((((st1 * st1 * n1) + (m1 * m1 * n1) + (st2 * st2 * n2) + (m2 * m2 * n2)) / nt) - (new_mean * new_mean)); //new stddev calculation
}

// the following are adapted from marks_bst.c of A7Q2

void display_stats(MARKS *sd) {
	printf("\nStatistics summary\n");
	printf("%s:%d\n", "count", sd->count);
	printf("%s:%.1f\n", "mean", sd->mean);
	printf("%s:%.1f\n", "stddev", sd->stddev);
}

void add_data(MARKS *sd, char *name, float score) {
	if (search(sd->bst, name) == NULL) {
		insert(&sd->bst, name, score);

		//recompute statistics summary by adding new one
		int count = sd->count;
		float mean = sd->mean;
		float stddev = sd->stddev;
		sd->count = count + 1;
		sd->mean = (mean * count + score) / (count + 1);
		sd->stddev = sqrt(score * score / (count + 1.0) + (stddev * stddev + mean * mean) * (count / (count + 1.0)) - sd->mean * sd->mean);

	} else
		printf("record exit");

}

void remove_data(MARKS *sd, char *name) {
	TNODE *np = NULL;
	if ((np = search(sd->bst, name)) != NULL) {
		float score = np->data.score;
		delete(&sd->bst, name);

		//recompute statistics summary by removing an old one
		int count = sd->count;
		float mean = sd->mean;
		float stddev = sd->stddev;
		sd->count = count - 1;
		sd->mean = (mean * count - score) / (count - 1.0);
		sd->stddev = sqrt((stddev * stddev + mean * mean) * (count / (count - 1.0)) - score * score / (count - 1.0) - sd->mean * sd->mean);

	} else
		printf("record not exit");
}

void display_marks(MARKS *dsp) {
	display_inorder_lines(dsp->bst);
	printf("\nstatistics summary\n");
	printf("%s:%d\n", "count", dsp->count);
	printf("%s:%.1f\n", "mean", dsp->mean);
	printf("%s:%.1f\n", "stddev", dsp->stddev);
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
	char delimiters[] = ",\n";
	float score = 0;
	int count = 0;
	float mean = 0, stddev = 0;

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
			count++;
			mean += score;
			stddev += score * score;
			insert(&ds->bst, name, score);
		}
	}

	ds->count = count;
	mean /= count;
	ds->mean = mean;
	ds->stddev = sqrt(stddev / count - mean * mean);

	fclose(fp);
}

void report_data(MARKS *sd, char *filename) {
	FILE *fp = fopen(filename, "w");

	print_to_file_inorder(sd->bst, fp);

	fprintf(fp, "\nStatistics summary\n");
	fprintf(fp, "%s:%d\n", "count", sd->count);
	fprintf(fp, "%s:%.1f\n", "mean", sd->mean);
	fprintf(fp, "%s:%.1f\n", "stddev", sd->stddev);
	fclose(fp);
}

void print_to_file_inorder(TNODE *root, FILE *fp) {
	if (root) {
		if (root->left)
			print_to_file_inorder(root->left, fp);
		fprintf(fp, "%s,%.1f,%c\n", root->data.name, root->data.score, letter_grade(root->data.score));
		if (root->right)
			print_to_file_inorder(root->right, fp);
	}
}

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
