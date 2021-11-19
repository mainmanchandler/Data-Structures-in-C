#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "marks_bst.h"

void search_info(char *sf, char *key, TNODE *tnp) {
	if (tnp)
		printf("%s(%s):%s %.0f\n", sf, key, tnp->data.name, tnp->data.score);
	else
		printf("%s(%s):NULL\n", sf, key);
}

int main(int argc, char *args[]) {
	char infilename[40] = "marks.txt";
	char outfilename[40] = "report.txt";
	if (argc > 1) {
		if (argc >= 2)
			strcpy(infilename, args[1]);
		if (argc >= 3)
			strcpy(outfilename, args[2]);
	}

	// load mark data to MARKS data structure
	MARKS ds = { 0 };
	import_data(&ds, infilename);
	display_marks(&ds); //count, mean, stddev,

	// test bst search
	char *key = "Smith";
	TNODE *tp = search(ds.bst, key);
	search_info("search", key, tp);

	// testing add data operation
	key = "Moore";
	float score = 92;
	add_data(&ds, "Moore", score);
	tp = search(ds.bst, key);
	search_info("search", key, tp);

	// testing remove data operation
	key = "Wang";
	remove_data(&ds, key);
	tp = search(ds.bst, key);
	search_info("search", key, tp);

	report_data(&ds, outfilename);
	clean_marks(&ds);

	FILE *fp = fopen(outfilename, "r");
	if (fp == NULL) {
		printf("output file does not exist\n");
		return 0;
	}
	char buf[100];
	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
		buf[0] = 0;
	}
	fclose(fp);

	return 0;
}

