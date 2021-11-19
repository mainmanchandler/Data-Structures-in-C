/*
 -------------------------------------
 File:    caseflip.c
 file description
 The user inputs a letter and returned its ASCII
 value and its corresponding capital or lower case
 counter part.
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-01-14
 -------------------------------------
 */

#include <stdio.h>

int main() {

	//this causes the none-buffered output in eclipse
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//variable init
	char c = 0, temp;

	do {
		printf("Please enter a character\n");
		scanf("%c", &c); // this is to get the character input from the keyboard

		//the loop below is to get rid of additional characters in the stdin buffer
		do {
			scanf("%c", &temp);

			if (temp == '\n')
				break;
		} while (1);

		if (c >= 'a' && c <= 'z' && c != '*') {
			printf("%c:%d,%c\n", c, c, c - 32);

		} else if (c >= 'A' && c <= 'Z' && c != '*') {
			printf("%c:%d,%c\n", c, c, c + 32);

		} else if (c != '*') {
			printf("%c:invalid\n", c);
		}

	} while (c != '*');

	printf("%c:quit\n", c);

	return 0;

}

