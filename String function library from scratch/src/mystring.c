/*
 -------------------------------------
 File:    mystring.c
 file description
 string functions
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-02
 -------------------------------------
 */

#include "mystring.h"
#define NULL 0

/*
 -------------------------------------------------------
 Reads from a char array and returns the length of the
 string sentence array
 Use: str_length(char *s)
 -------------------------------------------------------
 Parameters:
 *s - pointer to the first char in the sentence (pointer)
 Returns:
 length - the length of the sentence
 -------------------------------------------------------
 */
int str_length(char *s) {
	int length = 0;

	while (*s != '\0') { //isnt the end of the char array
		length += 1;
		s++;
	}

	return length;
}

/*
 -------------------------------------------------------
 Reads from a char array and the number of words
 Use: word_count(char *s)
 -------------------------------------------------------
 Parameters:
 *s - pointer to the first char in the sentence (pointer)
 Returns:
 word - the number of words
 -------------------------------------------------------
 */
int word_count(char *s) {
	int words = 0;

	while (*s != '\0') {
		//if the character isnt the end, is a space, and if the next char is not a space then;
		if (*(s + 1) != '\0' && *s == ' ' && *(s + 1) != ' ') {
			words += 1;
		}
		s++;
	}

	return words;
}

/*
 -------------------------------------------------------
 turns every char in a sentence array to lowercase
 Use: lower_case(char *s)
 -------------------------------------------------------
 Parameters:
 *s - pointer to the first char in the sentence (pointer)
 Returns:
 None
 -------------------------------------------------------
 */
void lower_case(char *s) {

	while (*s != '\0') {

		if (*s >= 'A' && *s <= 'Z') {
			*s = *s + 32; //this moves the value of the char on the ascii table
		}
		s++;
	}

	return;
}

/*
 -------------------------------------------------------
 Removes any unnecessary spaces in a sentence array
 Use: trim(char *s)
 -------------------------------------------------------
 Parameters:
 *s - pointer to the first char in the sentence (pointer)
 Returns:
 None
 -------------------------------------------------------
 */
void trim(char *s) {

	int i = 0, j = 0;

	while (s[i] != 0) {
		if (s[i] != ' ' || (i > 0 && s[i - 1] != ' ')) {
			s[j++] = s[i];
		}
		i += 1;
	}

	if (s[i - 1] == ' ') {
		s[j - 1] = '\0';
	} else {
		s[j] = '\0';
	}

	return;

}

