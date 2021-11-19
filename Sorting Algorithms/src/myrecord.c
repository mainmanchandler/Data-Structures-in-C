/*
 -------------------------------------
 File:    myrecord.c
 file description
 grade report functions
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-10
 -------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"

#define MAX_LINE 100

/*
 This function converts a float score to a letter grade according to ranges  S=[90, 100], A=[80, 90), B=[70, 80), C=[60, 70), D=[50,60), F=[0,50),
 and returns the letter grade.
 */
char letter_grade(float s) {
	char grade;

	if (s >= 90)
		grade = 'S';
	else if (s >= 80 && s < 90)
		grade = 'A';
	else if (s >= 70 && s < 80)
		grade = 'B';
	else if (s >= 60 && s < 70)
		grade = 'C';
	else if (s >= 50 && s < 60)
		grade = 'D';
	else if (s >= 0 && s < 50)
		grade = 'F';

	return grade;
}

/*
 This function imports data from file of name passed by filename, and stores all record entries in an array of
 RECORD dataset[], and returns the number of records read.
 */
int import_data(RECORD dataset[], char *filename) {
	char delimiters[] = ",\n\r";
	char *token = NULL;
	char record[100]; //MAX_REC = 100

	FILE *data = fopen(filename, "r");
	if (data == NULL)
		return -69; //error check

	int counter = 0;
	while (fgets(record, sizeof(record), data) != NULL) {	//(!feof(data)) { //read to the end of file, note: !feof runs one too many times and breaks the code

		token = (char*) strtok(record, delimiters);

		//grab the name in report
		strcpy(dataset[counter].name, token);

		//grab the grade in report
		token = (char*) strtok(NULL, delimiters);
		dataset[counter].score = atof(token); //converts string to float

		counter += 1;
	}

	fclose(data);
	return counter;
}

/*
 This function computes the average score, and standard deviation of the score values of dataset[], and returns the
 results by the RECORD type. It also outputs name and letter grade to file of name passed by filename, using format "%s,%c\n"
 */
REPORT report_data(RECORD dataset[], int n, char *filename) {
	REPORT report = { };
	if (n < 1)
		return report;

	//file to write to
	FILE *outfile = fopen(filename, "w");

	float mean = 0.0;
	float squared_sum = 0.0;
	float stddev = 0.0;
	for (int i = 0; i < n; i++) {
		fprintf(outfile, "%s,%c\n", dataset[i].name, letter_grade(dataset[i].score)); //print to the report file
		mean += dataset[i].score;
		squared_sum += dataset[i].score * dataset[i].score; //xi variable for standard deviation
	}
	mean = mean / n; //calculate mean
	stddev = sqrt((squared_sum / n) - (mean * mean)); //calculate standard deviation

	//update report data structure
	report.count = n;
	report.mean = mean;
	report.stddev = stddev;

	fclose(outfile);

	return report;
}

